/**
 * \file    types.h
 *
 * \brief   This file defines the basic data types used to fixed length types.
 *          Currently the standard types defined in stdint.h are used. This
 *          file also contains macros defining the TRUE,FALSE and NULLi pointer
 *          values.
 *
 *  \date   Aug 6, 2017
 *  \author Mohab Adel
 */

#ifndef TYPES_H_
#define TYPES_H_

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Defines TRUE status value */
#ifndef TRUE
#define TRUE     (1U)
#endif

/** \brief Defines FALSE status value */
#ifndef FALSE
#define FALSE    (0U)
#endif

/** \brief Defines NULL pointer value */
#ifndef NULL
#define NULL ((void*) 0U)
#endif

/** \brief create a 32 bit unsigned type */
typedef unsigned int uint32;

/** \brief create a 8 bit unsigned type */
typedef unsigned char uint8;

/** \brief create a 16 bit unsigned type */
typedef unsigned short uint16;

/** \brif create a 32 float point type */
typedef float fp32;

/** \brief create a 64 float point type */
typedef double fp64;


#endif /* TYPES_H_ */
