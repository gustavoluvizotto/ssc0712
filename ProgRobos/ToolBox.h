#ifndef TOOLBOX_H
#define	TOOLBOX_H

#include "Robot.h"
#include "Matrix.h"

namespace ToolBox {
    extern void FillVisionMatrix(Robot*, Matrix&, double=3, double=3, double=3);
    extern double GetProfDistance(Matrix&);
}

#endif	/* TOOLBOX_H */