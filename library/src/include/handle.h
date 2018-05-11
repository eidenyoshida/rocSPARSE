/* ************************************************************************
 * Copyright 2018 Advanced Micro Devices, Inc.
 * ************************************************************************ */

#pragma once
#ifndef HANDLE_H
#define HANDLE_H

#include "rocsparse.h"

#include <iostream>
#include <fstream>
#include <hip/hip_runtime_api.h>

/********************************************************************************
 * \brief rocsparse_handle is a structure holding the rocsparse library context.
 * It must be initialized using rocsparse_create_handle()
 * and the returned handle must be passed
 * to all subsequent library function calls.
 * It should be destroyed at the end using rocsparse_destroy_handle().
 *******************************************************************************/
struct _rocsparse_handle
{
    // Constructor
    _rocsparse_handle();
    // Destructor
    ~_rocsparse_handle();

    // Set stream
    rocsparse_status set_stream(hipStream_t user_stream);
    // Get stream
    rocsparse_status get_stream(hipStream_t *user_stream) const;

    // device id
    rocsparse_int device;
    // device properties
    hipDeviceProp_t properties;
    // device warp size
    rocsparse_int warp_size;
    // stream ; default stream is system stream NULL
    hipStream_t stream = 0;
    // pointer mode ; default mode is host
    rocsparse_pointer_mode pointer_mode = rocsparse_pointer_mode_host;
    // logging mode
    rocsparse_layer_mode layer_mode;

    // logging streams
    std::ofstream log_trace_ofs;
    std::ofstream log_bench_ofs;
    std::ostream *log_trace_os;
    std::ostream *log_bench_os;
};

/********************************************************************************
 * \brief rocsparse_mat_descr is a structure holding the rocsparse matrix
 * descriptor. It must be initialized using rocsparse_create_mat_descr()
 * and the retured handle must be passed to all subsequent library function
 * calls that involve the matrix.
 * It should be destroyed at the end using rocsparse_destroy_mat_descr().
 *******************************************************************************/
struct _rocsparse_mat_descr
{
    // Matrix type
    rocsparse_matrix_type type = rocsparse_matrix_type_general;
    // Fill mode TODO
//    rocsparse_fill_mode fill;
    // Diagonal type
//    rocsparse_diag_type diag;
    // Index base
    rocsparse_index_base base = rocsparse_index_base_zero;
};

/********************************************************************************
 * \brief rocsparse_hyb_mat is a structure holding the rocsparse HYB matrix.
 * It must be initialized using rocsparse_create_hyb_mat() and the returned
 * handle must be passed to all subsequent library function calls that involve
 * the HYB matrix.
 * It should be destroyed at the end using rocsparse_destroy_hyb_mat().
 *******************************************************************************/
struct _rocsparse_hyb_mat
{
    // num rows
    rocsparse_int m = 0;
    // num cols
    rocsparse_int n = 0;
    // partition type
    rocsparse_hyb_partition partition = rocsparse_hyb_partition_auto;
    // ELL matrix part
    rocsparse_int  ell_nnz     = 0;
    rocsparse_int  ell_width   = 0;
    rocsparse_int *ell_col_ind = nullptr;
    void          *ell_val     = nullptr;
    // COO matrix part
    rocsparse_int  coo_nnz     = 0;
    rocsparse_int *coo_row_ind = nullptr;
    rocsparse_int *coo_col_ind = nullptr;
    void          *coo_val     = nullptr;
};

/********************************************************************************
 * \brief ELL format indexing
 *******************************************************************************/
#define ELL_IND_ROW(i, el, m, width) (el) * (m) + (i)
#define ELL_IND_EL (i, el, m, width) (el) + (width) * (i)
#define ELL_IND(i, el, m, width) ELL_IND_ROW(i, el, m, width)

#endif // HANDLE_H