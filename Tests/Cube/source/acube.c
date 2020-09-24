/*---------------------------------------------------------------------------------

	a simple rotating cube demo by tkcne

---------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <gcmodplay.h>
#include <debug.h>
#include <ogcsys.h>

#define DEFAULT_FIFO_SIZE	(256*1024)		//GX_FIFO_MINSIZE

//---------------------------------------------------------------------------------
// cube vertex data
//---------------------------------------------------------------------------------
s16 cube[] ATTRIBUTE_ALIGN(32) = {
	// x y z
	-30,  30, -30, 	// 0
	 30,  30, -30, 	// 1
	 30,  30,  30, 	// 2
	-30,  30,  30, 	// 3
	 30, -30, -30, 	// 4
	 30, -30,  30, 	// 5
	-30, -30,  30,  // 6
	-30, -30, -30,  // 7
};


//---------------------------------------------------------------------------------
// color data
//---------------------------------------------------------------------------------
u8 colors[] ATTRIBUTE_ALIGN(32) = {
	// r, g, b, a
	100,  10, 100, 255, // 0 purple
	240,   0,   0, 255,	// 1 red
	255, 180,   0, 255,	// 2 orange
	255, 255,   0, 255, // 3 yellow
	 10, 120,  40, 255, // 4 green
	  0,  20, 100, 255  // 5 blue
};



GXRModeObj	*screenMode;
static void	*frameBuffer;
static vu8	readyForCopy;
#define	FIFO_SIZE (256*1024)

void draw_init();
void draw_cube(Mtx v);
static void	copy_buffers(u32 unused);

#define SIIOBUFFER 0xCC006480
void out_to_SIO(u32 value) {
    u32* SIO_ptr = SIIOBUFFER;
    *SIO_ptr = value;
}

int	main(void)
{
	Mtx	view;
	Mtx	projection;
	PADStatus pads[4];
	GXColor	backgroundColor	= {139, 23, 212,	255};
	void *fifoBuffer = NULL;

	VIDEO_Init();

	// some initialization
	screenMode = VIDEO_GetPreferredMode(NULL);

	PAD_Init();
	frameBuffer	= MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenMode));

	VIDEO_Configure(screenMode);
	VIDEO_SetNextFramebuffer(frameBuffer);
	VIDEO_SetPostRetraceCallback(copy_buffers);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();

	// initialize fifo buffer to some address in K1 (c0000000) RAM of size 0x40000
	fifoBuffer = MEM_K0_TO_K1(memalign(32,FIFO_SIZE));
	memset(fifoBuffer,	0, FIFO_SIZE);

	GX_Init(fifoBuffer, FIFO_SIZE);


	GX_SetCopyClear(backgroundColor, 0x00ffffff);
	GX_SetViewport(0,0,screenMode->fbWidth,screenMode->efbHeight,0,1);
	GX_SetDispCopyYScale((f32)screenMode->xfbHeight/(f32)screenMode->efbHeight);
	GX_SetScissor(0,0,screenMode->fbWidth,screenMode->efbHeight);
	GX_SetDispCopySrc(0,0,screenMode->fbWidth,screenMode->efbHeight);
	GX_SetDispCopyDst(screenMode->fbWidth,screenMode->xfbHeight);
	GX_SetCopyFilter(screenMode->aa,screenMode->sample_pattern,
					 GX_TRUE,screenMode->vfilter);
	GX_SetFieldMode(screenMode->field_rendering,
					((screenMode->viHeight==2*screenMode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(frameBuffer,GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);

	guVector camera =	{0.0F, 0.0F, 0.0F};
	guVector up =	{0.0F, 1.0F, 0.0F};
	guVector look	= {0.0F, 0.0F, -1.0F};

	guPerspective(projection, 60, 1.33F, 10.0F,	300.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);

	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_INDEX8);
	GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX8);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetArray(GX_VA_POS, cube, 3*sizeof(s16));
	GX_SetArray(GX_VA_CLR0, colors, 4*sizeof(u8));
	GX_SetNumChans(1);
	GX_SetNumTexGens(0);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

	while (1)
	{
        out_to_SIO(0xc0000000);
		guLookAt(view, &camera,	&up, &look);
		out_to_SIO(0xc0000001);
		GX_SetViewport(0,0,screenMode->fbWidth,screenMode->efbHeight,0,1);
		out_to_SIO(0xc0000002);
		GX_InvVtxCache();
		out_to_SIO(0xc0000003);
		GX_InvalidateTexAll();
		out_to_SIO(0xc0000004);
		draw_cube(view);
        out_to_SIO(0xc0000005);
		PAD_Read(pads);
		out_to_SIO(0xc0000006);
		if (pads[0].button & PAD_BUTTON_START) {
			void (*reload)() = (void(*)())0x80001800;
			reload();
		}
        out_to_SIO(0xc0000007);
	}
	return 0;
}

//---------------------------------------------------------------------------------
// draws a quad from 4 vertex idx and one color idx
//---------------------------------------------------------------------------------
void draw_quad(u8 v0, u8 v1, u8 v2, u8 v3, u8 c) {
//---------------------------------------------------------------------------------
	// one 8bit position idx
	GX_Position1x8(v0);
	// one 8bit color idx
	GX_Color1x8(c);
	GX_Position1x8(v1);
	GX_Color1x8(c);
	GX_Position1x8(v2);
	GX_Color1x8(c);
	GX_Position1x8(v3);
	GX_Color1x8(c);
}


//---------------------------------------------------------------------------------
void draw_cube(Mtx v) {
//---------------------------------------------------------------------------------
	Mtx m; // model matrix.
	Mtx mv; // modelview matrix.
	guVector axis = {-1,1,0};
	static float rotateby = 60;

	rotateby ++;

	// move the cube out in front of us and rotate it
	guMtxIdentity(m);
	guMtxRotAxisDeg(m, &axis, rotateby);
	guMtxTransApply(m, m, 0.0F, 0.0F, -200.0F);
	guMtxConcat(v,m,mv);
	// load the modelview matrix into matrix memory
	GX_LoadPosMtxImm(mv, GX_PNMTX0);

	// drawing begins!
	// tells the flipper what type of primitive we will be drawing
	// which descriptor in the VAT to use and the number of vertices
	// to expect. 24 since we will draw 6 quads with 4 verts each.
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);

		draw_quad(0, 3, 2, 1, 0);
		draw_quad(0, 7, 6, 3, 1);
		draw_quad(0, 1, 4, 7, 2);
		draw_quad(1, 2, 5, 4, 3);
		draw_quad(2, 3, 6, 5, 4);
		draw_quad(4, 7, 6, 5, 5);

	GX_End();

    out_to_SIO(0x68);
	GX_DrawDone();
	readyForCopy = GX_TRUE;

    out_to_SIO(0x69);
	VIDEO_WaitVSync();

    out_to_SIO(0x70);
}

static void	copy_buffers(u32 count __attribute__ ((unused)))
{
	if (readyForCopy==GX_TRUE) {
		GX_SetZMode(GX_TRUE, GX_LEQUAL,	GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
		GX_CopyDisp(frameBuffer,GX_TRUE);
		GX_Flush();
		readyForCopy = GX_FALSE;
	}
}
