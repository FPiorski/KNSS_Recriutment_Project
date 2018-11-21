#ifndef __ERRORS_H_INCLUDED
#define __ERRORS_H_INCLUDED

void FP_Error_Handler(char *, int);

#define HandleError() FP_Error_Handler(__FILE__, __LINE__)

#endif
