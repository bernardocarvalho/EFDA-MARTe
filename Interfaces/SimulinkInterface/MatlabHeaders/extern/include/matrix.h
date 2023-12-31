/*
 * @(#)matrix.h    generated by: makeheader 5.1.5  Fri Jul 20 17:25:52 2012
 *
 *		built from:	../../src/include/copyright.h
 *				../../src/include/pragma_interface.h
 *				include/published_version.h
 *				include/symver.h
 *				export/include/matrix/detail/published_fwd_decls.hpp
 *				alloccbk.cpp
 *				alloclst.cpp
 *				array.cpp
 *				array2.cpp
 *				arraycbk.cpp
 *				arraycpy.cpp
 *				assignmt.cpp
 *				bytestr.cpp
 *				catenate.cpp
 *				cellindex.cpp
 *				checkdim.cpp
 *				compat32.cpp
 *				conversions.cpp
 *				end.cpp
 *				errmsg.cpp
 *				error.cpp
 *				fmxapi.cpp
 *				fmxapi_700.cpp
 *				fmxapi_730.cpp
 *				funhdl.cpp
 *				grow.cpp
 *				ieee_wrap.cpp
 *				indexcpy.cpp
 *				iocbk.cpp
 *				marshal.cpp
 *				mcat.cpp
 *				mxarray_alloc.cpp
 *				mxassert.cpp
 *				mxequal.cpp
 *				mxuint128.cpp
 *				mxutil.cpp
 *				nargchk.cpp
 *				numconv.cpp
 *				opaque.cpp
 *				permute.cpp
 *				populate.cpp
 *				protected.cpp
 *				referenc.cpp
 *				resize.cpp
 *				rndcolon.cpp
 *				rootrecord_debug.cpp
 *				scopemgr.cpp
 *				smart_ptr.cpp
 *				strconv.cpp
 *				subserror.cpp
 *				transpose.cpp
 *				txtcmp.cpp
 *				undoc.cpp
 *				warning.cpp
 *				zbuffer.cpp
 *				include/compat_pub.h
 */

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

#ifndef matrix_h
#define matrix_h


/*
 * Copyright 1984-2003 The MathWorks, Inc.
 * All Rights Reserved.
 */



/* Copyright 2003-2006 The MathWorks, Inc. */

/* Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C extern
#endif

#endif


/* Version 7.4.0 */
#define MX_API_VER 0x07040000



#ifndef matrix_symver_h

/*
 * PUBLISHED APIs with changes in MATLAB 7.3
 */

#if !defined(MX_COMPAT_32) || defined(MX_INTERNAL_730)

/*
 * Include this uniformly on non-Linux platforms (no .symver)
 * Include it only internal to the matrix library on Linux
 */
#if !defined(__linux__) || defined(MX_INTERNAL_730)

#ifndef mxSetProperty
# define mxSetProperty mxSetProperty_730
#endif

#ifndef mxGetProperty
# define mxGetProperty mxGetProperty_730
#endif

#ifndef mxSetField
# define mxSetField mxSetField_730
#endif

#ifndef mxSetFieldByNumber
# define mxSetFieldByNumber mxSetFieldByNumber_730
#endif

#ifndef mxGetFieldByNumber
# define mxGetFieldByNumber mxGetFieldByNumber_730
#endif

#ifndef mxGetField
# define mxGetField mxGetField_730
#endif

#ifndef mxCreateStructMatrix
# define mxCreateStructMatrix mxCreateStructMatrix_730
#endif

#ifndef mxCreateCellMatrix
# define mxCreateCellMatrix mxCreateCellMatrix_730
#endif

#ifndef mxCreateCharMatrixFromStrings
# define mxCreateCharMatrixFromStrings mxCreateCharMatrixFromStrings_730
#endif

#ifndef mxGetString
# define mxGetString mxGetString_730
#endif

#ifndef mxGetNumberOfDimensions
# define mxGetNumberOfDimensions mxGetNumberOfDimensions_730
#endif

#ifndef mxGetDimensions
# define mxGetDimensions mxGetDimensions_730
#endif

#ifndef mxSetDimensions
# define mxSetDimensions mxSetDimensions_730
#endif

#ifndef mxSetIr
# define mxSetIr mxSetIr_730
#endif

#ifndef mxGetIr
# define mxGetIr mxGetIr_730
#endif

#ifndef mxSetJc
# define mxSetJc mxSetJc_730
#endif

#ifndef mxGetJc
# define mxGetJc mxGetJc_730
#endif

#ifndef mxCreateStructArray
# define mxCreateStructArray mxCreateStructArray_730
#endif

#ifndef mxCreateCharArray
# define mxCreateCharArray mxCreateCharArray_730
#endif

#ifndef mxCreateNumericArray
# define mxCreateNumericArray mxCreateNumericArray_730
#endif

#ifndef mxCreateCellArray
# define mxCreateCellArray mxCreateCellArray_730
#endif

#ifndef mxCreateLogicalArray
# define mxCreateLogicalArray mxCreateLogicalArray_730
#endif

#ifndef mxGetCell
# define mxGetCell mxGetCell_730
#endif

#ifndef mxSetCell
# define mxSetCell mxSetCell_730
#endif

#ifndef mxSetNzmax
# define mxSetNzmax mxSetNzmax_730
#endif

#ifndef mxSetN
# define mxSetN mxSetN_730
#endif

#ifndef mxSetM
# define mxSetM mxSetM_730
#endif

#ifndef mxGetNzmax
# define mxGetNzmax mxGetNzmax_730
#endif

#ifndef mxCreateDoubleMatrix
# define mxCreateDoubleMatrix mxCreateDoubleMatrix_730
#endif

#ifndef mxCreateNumericMatrix
# define mxCreateNumericMatrix mxCreateNumericMatrix_730
#endif

#ifndef mxCreateLogicalMatrix
# define mxCreateLogicalMatrix mxCreateLogicalMatrix_730
#endif

#ifndef mxCreateSparse
# define mxCreateSparse mxCreateSparse_730
#endif

#ifndef mxCreateSparseLogicalMatrix
# define mxCreateSparseLogicalMatrix mxCreateSparseLogicalMatrix_730
#endif

#ifndef mxGetNChars
# define mxGetNChars mxGetNChars_730
#endif

#ifndef mxCreateStringFromNChars
# define mxCreateStringFromNChars mxCreateStringFromNChars_730
#endif

#ifndef mxCalcSingleSubscript
# define mxCalcSingleSubscript mxCalcSingleSubscript_730
#endif

#ifndef mxGetDimensions_fcn
# define mxGetDimensions_fcn mxGetDimensions_730
#endif

#else

#ifndef mxGetDimensions_fcn
# define mxGetDimensions_fcn mxGetDimensions
#endif

#endif /* !__linux__ || MX_INTERNAL_730 */

#else

#ifndef mxGetDimensions_fcn
# define mxGetDimensions_fcn mxGetDimensions_700
#endif

#endif /* !MX_COMPAT_32 || MX_INTERNAL_730 */

#endif /* matrix_symver_h */



/* Copyright 2008-2010 The MathWorks, Inc. */

/*
 * NOTE: The contents of this header are ultimately PUBLISHED in
 * extern/include/matrix.h.
 */

#ifndef MATHWORKS_MATRIX_DETAIL_PUBLISHED_FWD_DECLS_HPP
#define MATHWORKS_MATRIX_DETAIL_PUBLISHED_FWD_DECLS_HPP

#include <stddef.h>
#include <tmwtypes.h>

/**
 * Forward declaration for mxArray
 */
typedef struct mxArray_tag mxArray;

/**
 * Type representing the signature for MEX functions.
 */
typedef void (*mxFunctionPtr) (int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/**
 * Maximum mxArray name length
 */
#define mxMAXNAM TMW_NAME_LENGTH_MAX

/**
 * Logical type
 */
typedef bool mxLogical;

/**
 * Typedef required for Unicode support in MATLAB
 */
typedef CHAR16_T mxChar;

/**
 * Enumeration corresponding to all the valid mxArray types.
 */
typedef enum
{
    mxUNKNOWN_CLASS = 0,
    mxCELL_CLASS,
    mxSTRUCT_CLASS,
    mxLOGICAL_CLASS,
    mxCHAR_CLASS,
    mxVOID_CLASS,
    mxDOUBLE_CLASS,
    mxSINGLE_CLASS,
    mxINT8_CLASS,
    mxUINT8_CLASS,
    mxINT16_CLASS,
    mxUINT16_CLASS,
    mxINT32_CLASS,
    mxUINT32_CLASS,
    mxINT64_CLASS,
    mxUINT64_CLASS,
    mxFUNCTION_CLASS,
    mxOPAQUE_CLASS,
    mxOBJECT_CLASS, /* keep the last real item in the list */
#if defined(_LP64) || defined(_WIN64)
    mxINDEX_CLASS = mxUINT64_CLASS,
#else
    mxINDEX_CLASS = mxUINT32_CLASS,
#endif
    /* TEMPORARY AND NASTY HACK UNTIL mxSPARSE_CLASS IS COMPLETELY ELIMINATED */
    mxSPARSE_CLASS = mxVOID_CLASS /* OBSOLETE! DO NOT USE */
}
mxClassID;

/**
 * Indicates whether floating-point mxArrays are real or complex.
 */
typedef enum
{
    mxREAL,
    mxCOMPLEX
}
mxComplexity;

#endif /* MATHWORKS_MATRIX_DETAIL_PUBLISHED_FWD_DECLS_HPP */


#include <stddef.h>	/* size_t */


/*
 * allocate memory, notifying registered listener
 */
EXTERN_C void *mxMalloc(
    size_t	n		/* number of bytes */
    );


/*
 * allocate cleared memory, notifying registered listener.
 */
EXTERN_C void *mxCalloc(
    size_t	n,	/* number of objects */
    size_t	size	/* size of objects */
    );


/*
 * free memory, notifying registered listener.
 */
EXTERN_C void mxFree(void *ptr)	/* pointer to memory to be freed */;


/*
 * reallocate memory, notifying registered listener.
 */
EXTERN_C void *mxRealloc(void *ptr, size_t size);

 
/*
 * Return the class (catergory) of data that the array holds.
 */
EXTERN_C mxClassID mxGetClassID(const mxArray *pa);


/*
 * Get pointer to data
 */
EXTERN_C void *mxGetData(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Set pointer to data
 */
EXTERN_C void mxSetData(
    mxArray *pa,		/* pointer to array */
    void  *newdata		/* pointer to data */
    );


/* 
 * Determine whether the specified array contains numeric (as opposed 
 * to cell or struct) data.
 */
EXTERN_C bool mxIsNumeric(const mxArray *pa);


/* 
 * Determine whether the given array is a cell array.
 */
EXTERN_C bool mxIsCell(const mxArray *pa);


/*
 * Determine whether the given array's logical flag is on.
 */ 
EXTERN_C bool mxIsLogical(const mxArray *pa);


/*  
 * Determine whether the given array contains character data. 
 */
EXTERN_C bool mxIsChar(const mxArray *pa);


/*
 * Determine whether the given array is a structure array.
 */
EXTERN_C bool mxIsStruct(const mxArray *pa);


/*
 * Determine whether the given array is an opaque array.
 */
EXTERN_C bool mxIsOpaque(const mxArray *pa);


/*
 * Returns true if specified array is a function object.
 */
EXTERN_C bool mxIsFunctionHandle(const mxArray *pa);


/*
 * This function is deprecated and is preserved only for backward compatibility.
 * DO NOT USE if possible.
 * Is array user defined MATLAB v5 object
 */
EXTERN_C bool mxIsObject(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Get imaginary data pointer for numeric array
 */
EXTERN_C void *mxGetImagData(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Set imaginary data pointer for numeric array
 */
EXTERN_C void mxSetImagData(
    mxArray *pa,		/* pointer to array */
    void    *newdata		/* imaginary data array pointer */
    );


/*
 * Determine whether the given array contains complex data.
 */
EXTERN_C bool mxIsComplex(const mxArray *pa);


/*
 * Determine whether the given array is a sparse (as opposed to full). 
 */
EXTERN_C bool mxIsSparse(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * double-precision floating-point numbers.
 */
EXTERN_C bool mxIsDouble(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * single-precision floating-point numbers.
 */
EXTERN_C bool mxIsSingle(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * signed 8-bit integers.
 */
EXTERN_C bool mxIsInt8(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * unsigned 8-bit integers.
 */
EXTERN_C bool mxIsUint8(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * signed 16-bit integers.
 */
EXTERN_C bool mxIsInt16(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * unsigned 16-bit integers.
 */
EXTERN_C bool mxIsUint16(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * signed 32-bit integers.
 */
EXTERN_C bool mxIsInt32(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * unsigned 32-bit integers.
 */
EXTERN_C bool mxIsUint32(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * signed 64-bit integers.
 */
EXTERN_C bool mxIsInt64(const mxArray *pa);


/*
 * Determine whether the specified array represents its data as 
 * unsigned 64-bit integers.
 */
EXTERN_C bool mxIsUint64(const mxArray *pa);


/*
 * Get number of dimensions in array
 */
EXTERN_C mwSize mxGetNumberOfDimensions(const mxArray *pa);


/*
 * Get pointer to dimension array
 */
EXTERN_C const mwSize *mxGetDimensions(const mxArray *pa);


/* 
 * Get number of elements in array
 */
EXTERN_C size_t mxGetNumberOfElements(	
    const mxArray *pa		/* pointer to array */
    );


/*
 * Get real data pointer for numeric array
 */
EXTERN_C double *mxGetPr(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Set real data pointer for numeric array
 */
EXTERN_C void mxSetPr(
    mxArray *pa,		/* pointer to array */
    double  *pr			/* real data array pointer */
    );


/*
 * Get imaginary data pointer for numeric array
 */
EXTERN_C double *mxGetPi(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Set imaginary data pointer for numeric array
 */
EXTERN_C void mxSetPi(
    mxArray *pa,		/* pointer to array */
    double  *pi			/* imaginary data array pointer */
    );


/*
 * Get string array data
 */
EXTERN_C mxChar *mxGetChars(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Get 8 bits of user data stored in the mxArray header.  NOTE: This state
 * of these bits are not guaranteed to be preserved after API function
 * calls.
 */
EXTERN_C int mxGetUserBits(
    const mxArray	*pa		/* pointer to array */
    );


/*
 * Set 8 bits of user data stored in the mxArray header. NOTE: This state
 * of these bits are not guaranteed to be preserved after API function
 * calls.
 */ 
EXTERN_C void mxSetUserBits(
	mxArray	*pa,		/* pointer to array */
	int	value
    );


/*
 * Get the real component of the specified array's first data element.
 */
EXTERN_C double mxGetScalar(const mxArray *pa);


/*
 * Inform Watcom compilers that scalar double return values
 * will be in the FPU register.
 */
#ifdef __WATCOMC__
#pragma aux mxGetScalar value [8087];
#endif


/*
 * Is the isFromGlobalWorkspace bit set?
 */
EXTERN_C bool mxIsFromGlobalWS(const mxArray *pa);


/*
 * Set the isFromGlobalWorkspace bit.
 */
EXTERN_C void mxSetFromGlobalWS(mxArray *pa, bool global);


/* 
 * Get row dimension
 */
EXTERN_C size_t mxGetM(const mxArray *pa);


/* 
 * Set row dimension
 */
EXTERN_C void mxSetM(mxArray *pa, mwSize m);


/* 
 * Get column dimension
 */
EXTERN_C size_t mxGetN(const mxArray *pa);


/*
 * Is array empty
 */
EXTERN_C bool mxIsEmpty(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Get row data pointer for sparse numeric array
 */
EXTERN_C mwIndex *mxGetIr(const mxArray *pa);


/*
 * Set row data pointer for numeric array
 */
EXTERN_C void mxSetIr(mxArray *pa, mwIndex *newir);


/*
 * Get column data pointer for sparse numeric array
 */
EXTERN_C mwIndex *mxGetJc(const mxArray *pa);


/*
 * Set column data pointer for numeric array
 */
EXTERN_C void mxSetJc(mxArray *pa, mwIndex *newjc);


/*
 * Get maximum nonzero elements for sparse numeric array
 */
EXTERN_C mwSize mxGetNzmax(const mxArray *pa);


/*
 * Set maximum nonzero elements for numeric array
 */
EXTERN_C void mxSetNzmax(mxArray *pa, mwSize nzmax);


/*
 * Get array data element size
 */
EXTERN_C size_t mxGetElementSize(const mxArray *pa);


/* 
 * Return the offset (in number of elements) from the beginning of 
 * the array to a given subscript.  
 */
EXTERN_C mwIndex mxCalcSingleSubscript(const mxArray *pa, mwSize nsubs, const mwIndex *subs);


/*
 * Get number of structure fields in array
 * Returns 0 if mxArray is non-struct.
 */
EXTERN_C int mxGetNumberOfFields(
    const mxArray *pa		/* pointer to array */
    );


/*
 * Get a pointer to the specified cell element. 
 */ 
EXTERN_C mxArray *mxGetCell(const mxArray *pa, mwIndex i);


/*
 * Set an element in a cell array to the specified value.
 */
EXTERN_C void mxSetCell(mxArray *pa, mwIndex i, mxArray *value);


/*
 * Return pointer to the nth field name
 */
EXTERN_C const char *mxGetFieldNameByNumber(const mxArray *pa, int n);


/*
 * Get the index to the named field.
 */ 
EXTERN_C int mxGetFieldNumber(const mxArray *pa, const char *name);


/*
 * Return a pointer to the contents of the named field for 
 * the ith element (zero based).
 */ 
EXTERN_C mxArray *mxGetFieldByNumber(const mxArray *pa, mwIndex i, int fieldnum);


/*
 * Set pa[i][fieldnum] = value 
 */
EXTERN_C void mxSetFieldByNumber(mxArray *pa, mwIndex i, int fieldnum, mxArray *value);


/*
 * Return a pointer to the contents of the named field for the ith 
 * element (zero based).  Returns NULL on no such field or if the
 * field itself is NULL
 */
EXTERN_C mxArray *mxGetField(const mxArray *pa, mwIndex i, const char *fieldname);


/*
 * Sets the contents of the named field for the ith element (zero based).  
 * The input 'value' is stored in the input array 'pa' - no copy is made.
 */
EXTERN_C void mxSetField(mxArray *pa, mwIndex i, const char *fieldname, mxArray *value);

 
/*
 * mxGetProperty returns the value of a property for a given object and index.
 * The property must be public.
 *
 * If the given property name doesn't exist, isn't public, or the object isn't
 * the right type, then mxGetProperty returns NULL.
 */
EXTERN_C mxArray *mxGetProperty(const mxArray *pa, const mwIndex i, const char *propname);

 
/*
 * mxSetProperty sets the value of a property for a given object and index.
 * The property must be public.
 *
 */
EXTERN_C void mxSetProperty(mxArray *pa, mwIndex i, const char *propname, const mxArray *value);

 
/* 
 * Return the name of an array's class.  
 */
EXTERN_C const char *mxGetClassName(const mxArray *pa);


/*
 * Determine whether an array is a member of the specified class. 
 */
EXTERN_C bool mxIsClass(const mxArray *pa, const char *name);


#include <stdlib.h>


#if !defined(MX_COMPAT_32) || defined(MX_INTERNAL_730)


/**
 * \copydoc mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateNumericMatrix(mwSize m, mwSize n, mxClassID classid, mxComplexity flag);


#endif

 
/* 
 * Set column dimension
 */
EXTERN_C void mxSetN(mxArray *pa, mwSize n);


/*
 * Set dimension array and number of dimensions.  Returns 0 on success and 1
 * if there was not enough memory available to reallocate the dimensions array.
 */
EXTERN_C int mxSetDimensions(mxArray *pa, const mwSize *size, mwSize ndims);


/*
 * mxArray destructor
 */
EXTERN_C void mxDestroyArray(mxArray *pa);


/**
 * \copydoc mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateNumericArray(mwSize ndim, const mwSize *dims, mxClassID classid, mxComplexity flag);


/**
 * \copybrief create_char
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateCharArray(mwSize ndim, const mwSize *dims);


/**
 * \copydoc mxCreateDoubleMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateDoubleMatrix(mwSize m, mwSize n, mxComplexity flag);


/*
 * Get a properly typed pointer to the elements of a logical array.
 */
EXTERN_C mxLogical *mxGetLogicals(const mxArray *pa);


/**
 * Create a logical array and initialize its data elements to false.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateLogicalArray(mwSize ndim, const mwSize *dims);


#if !defined(MX_COMPAT_32) || defined(MX_INTERNAL_730)


/**
 * Create a two-dimensional array to hold logical data and
 * initializes each data element to false.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateLogicalMatrix(mwSize m, mwSize n);


#endif


/**
 * Create a logical scalar mxArray having the specified value.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateLogicalScalar(bool value);


/*
 * Returns true if we have a valid logical scalar mxArray.
 */
EXTERN_C bool mxIsLogicalScalar(const mxArray *pa);


/*
 * Returns true if the logical scalar value is true.
 */
EXTERN_C bool mxIsLogicalScalarTrue(const mxArray *pa);


/**
 * Create a double-precision scalar mxArray initialized to the
 * value specified
 *
 * \copydoc mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateDoubleScalar(double value);


/**
 * \brief Create a 2-Dimensional sparse array.
 *
 * Z = mxCreateSparse(m,n,nzmax,cmplx_flag);
 * An m-by-n, real or complex, sparse matrix with room for nzmax nonzeros.
 * Use this to allocate storage for a sparse matrix.
 * It allocates the structure, allocates the pr, pi, ir and jc arrays,
 * and sets all the fields, which may be changed later.
 * Avoids the question of malloc(0) by replacing nzmax = 0 with nzmax = 1.
 * Also sets Z->pr[0] = 0.0 so that the scalar sparse(0.0) acts like 0.0.
 *
 * Notice that the value of m is almost irrelevant.  It is only stored in
 * the mxSetM field of the matrix structure.  It does not affect the amount
 * of storage required by sparse matrices, or the amount of time required
 * by sparse algorithms.  Consequently, m can be "infinite".  The result
 * is a semi-infinite matrix with a finite number of columns and a finite,
 * but unspecified, number of nonzero rows.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateSparse(mwSize m, mwSize n, mwSize nzmax, mxComplexity flag);


/**
 * Create a 2-D sparse logical array
 *
 * \copydoc mxCreateSparseNumericMatrix
 */
EXTERN_C mxArray *mxCreateSparseLogicalMatrix(mwSize m, mwSize n, mwSize nzmax);


/*
 * Copies characters from a MATLAB array to a char array
 * This function will attempt to perform null termination if it is possible.
 * nChars is the number of bytes in the output buffer
 */
EXTERN_C void mxGetNChars(const mxArray *pa, char *buf, mwSize nChars);


/*
 * Converts a string array to a C-style string. The C-style string is in the
 * local codepage encoding. If the conversion for the entire Unicode string
 * cannot fit into the supplied character buffer, then the conversion includes
 * the last whole codepoint that will fit into the buffer. The string is thus
 * truncated at the greatest possible whole codepoint and does not split code-
 * points.
 */
EXTERN_C int mxGetString(const mxArray *pa, char *buf, mwSize buflen);


/*
 * Create a NULL terminated C string from an mxArray of type mxCHAR_CLASS
 * Supports multibyte character sets.  The resulting string must be freed
 * with mxFree.  Returns NULL on out of memory or non-character arrays.
 */
EXTERN_C char *mxArrayToString(const mxArray *pa);


/**
 * Create a 1-by-n string array initialized to str. The supplied string is
 * presumed to be in the local codepage encoding. The character data format
 * in the mxArray will be UTF-16.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateStringFromNChars(const char *str, mwSize n);


/**
 * \brief Create a 1-by-n string array initialized to null terminated string
 * where n is the length of the string.
 * 
 * \param src_ptr  A pointer to a source string data
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateString(const char *str);


/**
 * \copybrief mxCreateCharMatrixFromStrings_safe
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateCharMatrixFromStrings(mwSize m, const char **str);


/**
 * \copybrief create_cell
 *
 * \copydetails mxCreateNumericMatrixWithReuse 
 */
EXTERN_C mxArray *mxCreateCellMatrix(mwSize m, mwSize n);


/**
 * Create an N-Dimensional cell array, with each cell initialized
 * to NULL.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateCellArray(mwSize ndim, const mwSize *dims);


/**
 * \copybrief create_struct
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateStructMatrix(size_t m, size_t n, int nfields, const char **fieldnames);


/**
 * Create an N-Dimensional structure array having the specified fields;
 * initialize all values to NULL.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxCreateStructArray(mwSize ndim, const mwSize *dims, int nfields,
			     const char **fieldnames);


/**
 * Make a deep copy of an array, return a pointer to the copy.
 *
 * \copydetails mxCreateNumericMatrixWithReuse
 */
EXTERN_C mxArray *mxDuplicateArray(const mxArray *in);


/*
 * Set classname of an unvalidated object array.  It is illegal to
 * call this function on a previously validated object array.
 * Return 0 for success, 1 for failure.
 */
EXTERN_C int mxSetClassName(mxArray *pa, const char *classname);


/* 
 * Add a field to a structure array. Returns field number on success or -1
 * if inputs are invalid or an out of memory condition occurs.
 */
EXTERN_C int mxAddField(mxArray *pa, const char *fieldname);


/*
 * Remove a field from a structure array.  Does nothing if no such field exists.
 * Does not destroy the field itself.
*/
EXTERN_C void mxRemoveField(mxArray *pa, int field);


/*
 * Function for obtaining MATLAB's concept of EPS
 */
EXTERN_C double mxGetEps(void);


/*
 * Function for obtaining MATLAB's concept of INF (Used in MEX-File callback).
 */
EXTERN_C double mxGetInf(void);


/*
 * Function for obtaining MATLAB's concept of NaN (Used in MEX-File callback).
 */
EXTERN_C double mxGetNaN(void);


/*
 * Inform Watcom compilers that scalar double return values
 * will be in the FPU register.
 */
#ifdef __WATCOMC__
#pragma aux mxGetEps value [8087];
#pragma aux mxGetInf value [8087];
#pragma aux mxGetNaN value [8087];
#endif


/*
 * test for finiteness in a machine-independent manner
 */
EXTERN_C bool mxIsFinite(
    double x                  /* value to test */
    );


/*
 * test for infinity in a machine-independent manner
 */
EXTERN_C bool mxIsInf(
    double x                  /* value to test */
    );


/*
 * test for NaN in a machine-independent manner
 */
EXTERN_C bool mxIsNaN(
    double x                  /* value to test */
    );



/*
mxAssert(int expression, char *error_message)
---------------------------------------------

  Similar to ANSI C's assert() macro, the mxAssert macro checks the
  value of an assertion, continuing execution only if the assertion
  holds.  If 'expression' evaluates to be true, then the mxAssert does
  nothing.  If, however, 'expression' is false, then mxAssert prints an
  error message to the MATLAB Command Window, consisting of the failed
  assertion's expression, the file name and line number where the failed
  assertion occurred, and the string 'error_message'.  'error_message'
  allows the user to specify a more understandable description of why
  the assertion failed.  (Use an empty string if no extra description
  should follow the failed assertion message.)  After a failed
  assertion, control returns to the MATLAB command line. 

  mxAssertS, (the S for Simple), takes the same inputs as mxAssert.  It 
  does not print the text of the failed assertion, only the file and 
  line where the assertion failed, and the explanatory error_message.

  Note that script MEX will turn off these assertions when building
  optimized MEX-functions, so they should be used for debugging 
  purposes only.
*/

#ifdef MATLAB_MEX_FILE
#  ifndef NDEBUG

EXTERN_C void mexPrintAssertion(const char *test, 
		       const char *fname, 
		       int linenum, 
		       const char *message);


#    define mxAssert(test, message) ( (test) ? (void) 0 : mexPrintAssertion(#test, __FILE__, __LINE__, message))
#    define mxAssertS(test, message) ( (test) ? (void) 0 : mexPrintAssertion("", __FILE__, __LINE__, message))
#  else
#    define mxAssert(test, message) ((void) 0)
#    define mxAssertS(test, message) ((void) 0)
#  endif
#else
#  include <assert.h>
#  define mxAssert(test, message) assert(test)
#  define mxAssertS(test, message) assert(test)
#endif



#include <stdlib.h>



#ifdef MX_COMPAT_32
/*
 * 32-bit compatibility APIs
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Cannot inline these one on 64-bit platforms */
#if defined(_LP64) || defined(_WIN64)
#undef mxGetDimensions
#undef mxSetDimensions
#undef mxSetIr
#undef mxGetIr
#undef mxSetJc
#undef mxGetJc
#undef mxCreateStructArray
#undef mxCreateCharArray
#undef mxCreateNumericArray
#undef mxCreateCellArray
#undef mxCreateLogicalArray
#undef mxGetM
#undef mxCalcSingleSubscript
#endif

#ifndef mxSetProperty
#define mxSetProperty mxSetProperty_700
#endif
void mxSetProperty_700(mxArray *, int, const char *, const mxArray *);

#ifndef mxGetProperty
#define mxGetProperty mxGetProperty_700
#endif
mxArray *mxGetProperty_700(const mxArray *, int, const char *);

#ifndef mxSetField
#define mxSetField mxSetField_700
#endif
void mxSetField_700(mxArray *, int, const char *, mxArray *);

#ifndef mxSetFieldByNumber
#define mxSetFieldByNumber mxSetFieldByNumber_700
#endif
void mxSetFieldByNumber_700(mxArray *, int, int, mxArray *);

#ifndef mxGetFieldByNumber
#define mxGetFieldByNumber mxGetFieldByNumber_700
#endif
mxArray *mxGetFieldByNumber_700(const mxArray *, int, int);

#ifndef mxGetField
#define mxGetField mxGetField_700
#endif
mxArray *mxGetField_700(const mxArray *, int, const char *);

#ifndef mxCreateStructMatrix
#define mxCreateStructMatrix mxCreateStructMatrix_700
#endif
mxArray *mxCreateStructMatrix_700(int, int, int, const char **);

#ifndef mxCreateCellMatrix
#define mxCreateCellMatrix mxCreateCellMatrix_700
#endif
mxArray *mxCreateCellMatrix_700(int, int);

#ifndef mxCreateCharMatrixFromStrings
#define mxCreateCharMatrixFromStrings mxCreateCharMatrixFromStrings_700
#endif
mxArray *mxCreateCharMatrixFromStrings_700(int, const char **);

#ifndef mxGetString
#define mxGetString mxGetString_700
#endif
int mxGetString_700(const mxArray *, char *, int);

#ifndef mxGetNumberOfDimensions
#define mxGetNumberOfDimensions mxGetNumberOfDimensions_700
#endif
int mxGetNumberOfDimensions_700(const mxArray *);

#ifndef mxGetDimensions
#define mxGetDimensions mxGetDimensions_700
#endif
const int *mxGetDimensions_700(const mxArray *);

#ifndef mxSetDimensions
#define mxSetDimensions mxSetDimensions_700
#endif
int mxSetDimensions_700(mxArray *, const int *, int);

#ifndef mxSetIr
#define mxSetIr mxSetIr_700
#endif
void mxSetIr_700(mxArray *, int *);

#ifndef mxGetIr
#define mxGetIr mxGetIr_700
#endif
int *mxGetIr_700(const mxArray *);

#ifndef mxSetJc
#define mxSetJc mxSetJc_700
#endif
void mxSetJc_700(mxArray *, int *);

#ifndef mxGetJc
#define mxGetJc mxGetJc_700
#endif
int *mxGetJc_700(const mxArray *);

#ifndef mxCreateStructArray
#define mxCreateStructArray mxCreateStructArray_700
#endif
mxArray *mxCreateStructArray_700(int, const int *, int, const char **);

#ifndef mxCreateCharArray
#define mxCreateCharArray mxCreateCharArray_700
#endif
mxArray *mxCreateCharArray_700(int, const int *);

#ifndef mxCreateNumericArray
#define mxCreateNumericArray mxCreateNumericArray_700
#endif
mxArray *mxCreateNumericArray_700(int, const int *, mxClassID, mxComplexity);

#ifndef mxCreateCellArray
#define mxCreateCellArray mxCreateCellArray_700
#endif
mxArray *mxCreateCellArray_700(int, const int *);

#ifndef mxCreateLogicalArray
#define mxCreateLogicalArray mxCreateLogicalArray_700
#endif
mxArray *mxCreateLogicalArray_700(int, const int *);

#ifndef mxGetCell
#define mxGetCell mxGetCell_700
#endif
mxArray *mxGetCell_700(const mxArray *, int);

#ifndef mxSetCell
#define mxSetCell mxSetCell_700
#endif
void mxSetCell_700(mxArray *, int, mxArray *);

#ifndef mxSetNzmax
#define mxSetNzmax mxSetNzmax_700
#endif
void mxSetNzmax_700(mxArray *, int);

#ifndef mxSetN
#define mxSetN mxSetN_700
#endif
void mxSetN_700(mxArray *, int);

#ifndef mxSetM
#define mxSetM mxSetM_700
#endif
void mxSetM_700(mxArray *, int);

#ifndef mxGetNzmax
#define mxGetNzmax mxGetNzmax_700
#endif
int mxGetNzmax_700(const mxArray *);

#ifndef mxCreateDoubleMatrix
#define mxCreateDoubleMatrix mxCreateDoubleMatrix_700
#endif
mxArray *mxCreateDoubleMatrix_700(int, int, mxComplexity);

#ifndef mxCreateNumericMatrix
#define mxCreateNumericMatrix mxCreateNumericMatrix_700
#endif
mxArray *mxCreateNumericMatrix_700(int, int, mxClassID, int);

#ifndef mxCreateLogicalMatrix
#define mxCreateLogicalMatrix mxCreateLogicalMatrix_700
#endif
mxArray *mxCreateLogicalMatrix_700(unsigned int, unsigned int);

#ifndef mxCreateSparse
#define mxCreateSparse mxCreateSparse_700
#endif
mxArray *mxCreateSparse_700(int, int, int, mxComplexity);

#ifndef mxCreateSparseLogicalMatrix
#define mxCreateSparseLogicalMatrix mxCreateSparseLogicalMatrix_700
#endif
mxArray *mxCreateSparseLogicalMatrix_700(int, int, int);

#ifndef mxGetNChars
#define mxGetNChars mxGetNChars_700
#endif
void mxGetNChars_700(const mxArray *, char *, int);

#ifndef mxCreateStringFromNChars
#define mxCreateStringFromNChars mxCreateStringFromNChars_700
#endif
mxArray *mxCreateStringFromNChars_700(const char *, int);

#ifndef mxCalcSingleSubscript
#define mxCalcSingleSubscript mxCalcSingleSubscript_700
#endif
int mxCalcSingleSubscript_700(const mxArray *, int, const int *);

#ifdef __cplusplus
}
#endif

#endif /* #ifdef MX_COMPAT_32 */


#endif /* matrix_h */
