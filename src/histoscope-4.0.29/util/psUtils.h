/*******************************************************************************
*									       *
* psUtils.h -- PostScript file output routines	Public Header File	       *
*									       *
* Copyright (c) 1991 Universities Research Association, Inc.		       *
* All rights reserved.							       *
* 									       *
* This material resulted from work developed under a Government Contract and   *
* is subject to the following license:  The Government retains a paid-up,      *
* nonexclusive, irrevocable worldwide license to reproduce, prepare derivative *
* works, perform publicly and display publicly by or for the Government,       *
* including the right to distribute to other Government contractors.  Neither  *
* the United States nor the United States Department of Energy, nor any of     *
* their employees, makes any warrenty, express or implied, or assumes any      *
* legal liability or responsibility for the accuracy, completeness, or         *
* usefulness of any information, apparatus, product, or process disclosed, or  *
* represents that its use would not infringe privately owned rights.           *
*                                        				       *
* Fermilab Nirvana GUI Library						       *
* April 16, 1992							       *
*									       *
* Written by Arnulfo Zepeda-Navratil				               *
*            Centro de Investigacion y Estudio Avanzados ( CINVESTAV )         *
*            Mexico                                                            *
*									       *
* With some portions from psFiles.c by Sanza T. Kazadi, Fermilab	       *
*									       *
*******************************************************************************/
/* SCCS ID: psUtils.h 1.10 6/18/96 */

enum outdevice {X_SCREEN, PS_PRINTER};
enum anchorModes {PS_LEFT, PS_CENTER, PS_RIGHT};

/* Amount of space to leave on the edge of the printer page in 72nds of an
   inch.  If this is too big, part of the page will be wasted, too small,
   and some (espescially color) printers will clip off part of the plot */
#define PAGE_MARGIN 18

typedef struct {
    float x1, y1, x2, y2;
} FloatSegment;

typedef struct {
    float x, y;
} FloatPoint;

FILE *OpenPS(char fname[], int width, int height);
void EndPS(void);
FILE *PSGetFile(void);
void PSSetFile(FILE *fp);
void PSSetWindowPagePosition(int bottom, int left, int width, int height);
void PSDrawSegments(Display *display, Drawable w, GC gc,
	XSegment *segment, int nsegments);
void PSDrawLine(Display *display, Drawable w, GC gc, int x1, int y1,
	int x2, int y2);
void PSDrawLines(Display *display, Drawable w, GC gc,
	XPoint *points, int nPoints, int mode);
void PSFloatDrawSegments(Display *display, Drawable w, GC gc, 
	FloatSegment *segment, int nSegments);
void PSFloatDrawLine(Display *display, Drawable w, GC gc,
	float x0, float y0, float x1, float y1);
void PSFloatDrawLines(Display *display, Drawable w, GC gc,
	FloatPoint *points, int nPoints);
void PSDrawPoint(Display *display, Drawable w, GC gc, int x, int y);
void PSDrawPoints(Display *display, Drawable w, GC gc,
	XPoint *point, int npoints, int mode);
void PSDrawRectangle(Display *display, Drawable w, GC gc, int x, int y,
	unsigned int width, unsigned int height);
void PSDrawDashedRectangle(Display *display, Drawable w, GC gc, int x, int y,
	unsigned width, unsigned height, char *dashList, int dashOffset);
void PSDrawRectangles(Display *display, Drawable w, GC gc,
	XRectangle *rects, int nRects);
void PSFillRectangle(Display *display, Drawable w, GC gc,
	int x, int y, unsigned int width, unsigned int height);
void PSFillRectangles(Display *display, Drawable w, GC gc,
	XRectangle *rects, int nRects);
void PSDrawArc(Display *display, Drawable w, GC gc,
	int x, int y, unsigned int width, unsigned int height,
	int angle1, int angle2);
void PSDrawArcs(Display *display, Drawable w, GC gc,
	XArc *arcs, int nArcs);
void PSFillArc(Display *display, Drawable w, GC gc,
	int x, int y, unsigned int width, unsigned int height,
	int angle1, int angle2);
void PSFillArcs(Display *display, Drawable w, GC gc,
	XArc *arcs, int nArcs);
void PSFloatDrawEllipse(Display *display, Drawable w, GC gc,
	float xc, float yc, float width, float height, float angle_deg);
void PSFloatFillEllipse(Display *display, Drawable w, GC gc,
	float xc, float yc, float width, float height, float angle_deg);
void PSFloatFillPolygon(Display *display, Drawable w, GC gc,
        FloatPoint *points, int nPoints);
void PSDrawString(Display *display, Drawable w, GC gc, XFontStruct *fs,
	int x, int y, int anchor, char *msg, char *psfont, int psfontsize);
void PSDrawXmString(Display *display, Drawable w, XmFontList font,
        XmString msg, GC gc, int x, int y, int width, int alignment,
        char *psfont, int psfontsize);
void PSDrawImage(Display *display, Drawable w, GC gc, int scanLength, 
	int scanLines, int bitsPerSample, int x, int y, unsigned char *bitmap);
void PSDrawDashedSegments(Display *display, Drawable w, GC gc, 
	XSegment *segments, int nSegments, char *dashList, int dashOffset);
void PSFloatDrawDashedSegments(Display *display, Drawable w, GC gc,
	FloatSegment *segment, int nSegments, char *dashList, int dashOffset);
void PSDrawDashedLine(Display *display, Drawable w, GC gc, int x1, int y1,
	int x2, int y2, char *dashList, int dashOffset);
void PSFloatDrawDashedLines(Display *display, Drawable w, GC gc,
	FloatPoint *points, int nPoints, char *dashList, int dashOffset);
void PSSetClipRectangle(int x1, int y1, int x2, int y2);
void PSSetClipRectangles(XRectangle *rects, int nRects);
void PSSetMinimumLineWidth(double width);
void PSImportEPS(const char *fileid, const char *psdata, 
		 int x, int y, unsigned int width, unsigned int height,
		 int xmin, int ymin, int xmax, int ymax);
