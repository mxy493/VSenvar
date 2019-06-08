/*  graphics.h

	在 VC 下模拟 Borland BGI 绘图库，实现简单的绘图

	2009-9-9 by yw80@msn.com
	http://hi.baidu.com/yangw80
*/

#pragma once

#pragma comment(lib,"graphics.lib")

/* debug 模式时不加载 release 模式的库文件 */
#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
#endif

#include "windows.h"

#define pointtype POINT
#define MAXCOLORS 0xffffff
#define PI 3.1415926535

/* 为了兼容 Borland C++ 3.1 而做的无意义定义 */
#define DETECT 0
#define VGA	0
#define VGAHI 0

/* 初始化参数 */
enum init_flags
{
	SHOWCONSOLE = 1		// 进入图形模式时，保留控制台的显示
};

/* 颜色常量设置 */
enum COLORS
{
	BLACK	= 0,
	BLUE	= 0xA80000,
	GREEN	= 0x00A800,
	CYAN	= 0xA8A800,
	RED		= 0x0000A8,
	MAGENTA	= 0xA800A8,
	BROWN	= 0x0054A8,
	LIGHTGRAY	= 0xA8A8A8,
	DARKGRAY	= 0x545454,
	LIGHTBLUE	= 0xFC5454,
	LIGHTGREEN	= 0x54FC54,
	LIGHTCYAN	= 0xFCFC54,
	LIGHTRED	= 0x5454FC,
	LIGHTMAGENTA= 0xFC54FC,
	YELLOW	= 0x54FCFC,
	WHITE	= 0xFCFCFC
};

/* 视图设置信息 */
struct viewporttype
{
	int left, top, right, bottom;
	int clip;
};

/* 线样式 */
enum line_styles
{
    SOLID_LINE   = 0,
    DOTTED_LINE  = 1,
    CENTER_LINE  = 2,
    DASHED_LINE  = 3,
    USERBIT_LINE = 4,   /* User defined line style */
};

/* 线宽 */
enum line_widths
{
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3,
};

/* 线形 */
struct linesettingstype
{
    int linestyle;
    unsigned upattern;
    int thickness;
};

/* 填充模式 */
enum fill_patterns
{
    EMPTY_FILL,		/* fills area in background color */
    SOLID_FILL,		/* fills area in solid fill color */
    LINE_FILL,		/* --- fill */
    LTSLASH_FILL,	/* /// fill */
    SLASH_FILL,		/* /// fill with thick lines */
    BKSLASH_FILL,	/* \\\ fill with thick lines */
    LTBKSLASH_FILL,	/* \\\ fill */
    HATCH_FILL,		/* light hatch fill */
    XHATCH_FILL,	/* heavy cross hatch fill */
    INTERLEAVE_FILL,/* interleaving line fill */
    WIDE_DOT_FILL,	/* Widely spaced dot fill */
    CLOSE_DOT_FILL,	/* Closely spaced dot fill */
    USER_FILL		/* user defined fill */
};

/* 填充类型 */
struct fillsettingstype
{
    int pattern;
    int color;
};

/* 圆弧坐标信息，应用于 getarccoords() */
struct arccoordstype
{
    int x, y;
    int xstart, ystart, xend, yend;
};

/* 位操作模式 */
enum putimage_ops
{
	COPY_PUT = SRCCOPY,		/* MOV */
	XOR_PUT = SRCINVERT,	/* XOR */
	OR_PUT = SRCPAINT,		/* OR  */
	AND_PUT = SRCAND,		/* AND */
	NOT_PUT = NOTSRCCOPY	/* NOT */
};

/* 定义图像 */
class IMAGE
{
private:
	HBITMAP m_hBmp;
	HDC m_hDC;
	int m_width, m_height;
public:
	IMAGE();
	~IMAGE();
	void getimage(int left, int top, int right, int bottom);
	void getimage(const char *imagefile);
	void getimage(const IMAGE *imgsrc, int left, int top, int right, int bottom);
	void putimage(int left, int top, int op);

	friend void IMAGE::getimage(const IMAGE *imgsrc, int left, int top, int right, int bottom);
};



/* 绘图模式相关函数 */

void initgraph(int* gdriver, int* gmode, char* path);	/* 兼容 Borland C++ 3.1 的重载，默认 640x480@24bit */
void initgraph(int Width, int Height);					/* 初始化图形环境 */
void initgraph(int Width, int Height, int Flag);		/* 初始化图形环境 */
void closegraph();										/* 关闭图形环境 */


/* 绘图环境设置 */

void cleardevice();					/* 清屏 */

COLORREF getcolor();				/* 获取当前绘图前景色 */
void setcolor(COLORREF color);		/* 设置当前绘图前景色 */
COLORREF getbkcolor();				/* 获取当前绘图背景色 */
void setbkcolor(COLORREF color);	/* 设置当前绘图背景色 */

void getviewsettings(struct viewporttype *viewport);					/* 获取视图信息 */
void setviewport(int left, int top, int right, int bottom, int clip);	/* 设置视图 */
void clearviewport();													/* 清空视图 */

void getlinesettings(struct linesettingstype *lineinfo);				/* 获取当前线形 */
void setlinestyle(int linestyle, unsigned int upattern, int thickness);	/* 设置当前线形 */

void getfillsettings(struct fillsettingstype *fillinfo);	/* 获取填充类型 */
void setfillstyle(int pattern, int color);					/* 设置填充类型 */
void getfillpattern(char *pattern);							/* 获取自定义填充类型 */
void setfillpattern(const char *upattern, int color);		/* 设置自定义填充类型 */

void getaspectratio(int *xasp, int *yasp);	/* 获取当前缩放因子 */
void setaspectratio(int xasp, int yasp);	/* 设置当前缩放因子 */

void setwritemode(int mode);				/* 设置绘图位操作模式 */

void graphdefaults();						/* 重置所有绘图设置为默认值 */


/* 绘图函数 */

COLORREF getpixel(int x, int y);				/* 获取点的颜色 */
void putpixel(int x, int y, COLORREF color);	/* 画点 */

void moveto(int x, int y);						/* 移动当前点(绝对坐标) */
void moverel(int dx, int dy);					/* 移动当前点(相对坐标) */

void line(int x1, int y1, int x2, int y2);		/* 画线 */
void linerel(int dx, int dy);					/* 画线(至相对坐标) */
void lineto(int x, int y);						/* 画线(至绝对坐标) */

void rectangle(int left, int top, int right, int bottom);	/* 画矩形 */

void getarccoords(struct arccoordstype *arccoords);								/* 获取圆弧坐标信息 */
void arc(int x, int y, int stangle, int endangle, int radius);					/* 画圆弧 */
void circle(int x, int y, int radius);											/* 画圆 */
void pieslice(int x, int y, int stangle, int endangle, int radius);				/* 画填充圆扇形 */
void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);/* 画椭圆弧线 */
void fillellipse(int x, int y, int xradius, int yradius);						/* 画填充椭圆 */
void sector(int x, int y, int stangle, int endangle, int xradius, int yradius);	/* 画填充椭圆扇形 */

void bar(int left, int top, int right, int bottom);								/* 画无边框填充矩形 */
void bar3d(int left, int top, int right, int bottom, int depth, int topflag);	/* 画有边框三维填充矩形 */

void drawpoly(int numpoints, const int *polypoints);	/* 画多边形 */
void fillpoly(int numpoints, const int *polypoints);	/* 画填充的多边形 */
void floodfill(int x, int y, int border);				/* 填充区域 */


/* 文字相关函数 */

void outtext(LPCTSTR textstring);					/* 在当前位置输出文字 */
void outtextxy(int x, int y, LPCTSTR textstring);	/* 在指定位置输出文字 */
int textwidth(LPCTSTR textstring);					/* 获取字符串占用的像素宽 */
int textheight(LPCTSTR textstring);					/* 获取字符串占用的像素高 */

/* 设置当前字体样式
		nHeight: 字符的平均高度
		nWidth: 字符的平均宽度
		nEscapement: 字符串的书写角度，单位 0.1 度。
		nOrientation: 每个字符的书写角度，单位 0.1 度。
		fnWeight: 字符的笔画粗细。常用的是 400，默认 0 即可。
		fdwItalic: 是否斜体，TRUE / FALSE
		fdwUnderline: 是否下划线，TRUE / FALSE
		fdwStrikeOut: 是否删除线，TRUE / FALSE
		lpszFace: 字体名称 */
void SetFont(int nHeight,int nWidth,int nEscapement,int nOrientation,int fnWeight,BYTE fdwItalic,BYTE fdwUnderline,BYTE fdwStrikeOut,LPCTSTR lpszFace);
void SetFont(const LOGFONT *font);	/* 设置当前字体样式 */
void GetFont(LOGFONT *font);		/* 获取当前字体样式 */


/* 图像处理函数 */

void getimage(int left, int top, int right, int bottom, IMAGE *imgdst);			/* 从屏幕获取图像 */
void getimage(const char *imagefile, IMAGE *imgdst);							/* 从 BMP 文件获取图像 */
void getimage(const IMAGE *imgsrc, int left, int top, int right, int bottom, IMAGE *imgdst);	/* 从 IMAGE 对象获取图像 */
void putimage(int left, int top, IMAGE *img, int op);							/* 绘制图像 */



/* 其它函数 */

int	getmaxcolor();	/* 获取最大颜色值 */
int	getmaxx();		/* 获取最大 x 坐标 */
int	getmaxy();		/* 获取最大 y 坐标 */
int	getx();			/* 获取当前 x 坐标 */
int	gety();			/* 获取当前 y 坐标 */
int GetGraphicsVer();		/* 获取当前版本 */
char* GetGraphicsAuthor();	/* 作者 */
