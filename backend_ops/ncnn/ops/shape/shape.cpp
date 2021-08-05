#include "shape.h"

#include "../ncnn_ops_definer.h"

namespace mmlab {
using namespace ncnn;
DEFINE_LAYER_CREATOR(Shape)
DEFINE_NCNN_OPS(Shape, Shape)
Shape::Shape() {
  one_blob_only = true;
  support_inplace = false;
}

int Shape::forward(const Mat &bottom_blob, Mat &top_blob,
                   const Option &opt) const {
  int dims = bottom_blob.dims;
  int w = bottom_blob.w;
  size_t elemsize = sizeof(bottom_blob.w);
  top_blob.create(dims, elemsize, opt.blob_allocator);
  if (top_blob.empty()) {
    return -100;
  }
  float *outptr = top_blob;
  if (dims == 1) {
    outptr[0] = w;
    return 0;
  }
  if (dims == 2) {
    int h = bottom_blob.h;
    outptr[0] = h;
    outptr[1] = w;
    return 0;
  }
  if (dims == 3) {
    int h = bottom_blob.h;
    int channels = bottom_blob.c;
    outptr[0] = channels;
    outptr[1] = h;
    outptr[2] = w;
    return 0;
  }
}

}  // namespace mmlab
