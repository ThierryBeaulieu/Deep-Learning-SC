#include "ap_axi_sdata.h"
#include "hls_stream.h"

void example(hls::stream<ap_axis<32,2,5,6>> &A, hls::stream<ap_axis<32,2,5,6>> &B)
{
#pragma HLS INTERFACE axis port=A
#pragma HLS INTERFACE axis port=B
#pragma HLS INTERFACE s_axilite port=return

	static int weights[10][401] = {
	    {-50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -2, -3, -3, 0, 0, 0, 0, 0, 0, 0, -2, -8, -13, -18, -10, -11, 0, 4, -1, 0, -7, -10, -15, -19, -18, 0, 0, 0, 0, 0, -1, -5, -41, -32, 0, 19, 29, 0, -7, 0, -16, -15, 26, 3, -17, -3, 0, 0, 0, -1, 22, 2, -12, -21, -11, 33, 21, -28, -17, -3, -24, -23, 54, 13, -45, -10, 0, 0, 0, -11, -4, -8, -21, -10, -14, -8, -16, -14, -10, -3, -14, -26, -27, -1, -26, -16, 0, 0, 0, -22, -38, -13, -16, 0, -11, 10, -34, -34, -18, -32, 19, 32, -12, -1, 0, -35, 0, 0, -3, -17, -9, -27, -20, 3, 2, -6, -33, -8, 7, -13, -27, 7, -2, -14, -22, -42, -6, 0, -6, -3, -10, -13, -6, -4, 2, 7, 8, 16, 10, 13, 10, 1, -21, -3, -4, -30, -1, 0, -3, 9, -20, -34, 4, -5, 9, 45, 44, 30, 34, 0, 19, 0, 1, -3, -23, -23, 0, 0, -2, 7, 30, 9, -7, -13, 27, 20, 6, -13, 2, -27, -17, 9, 13, 12, -39, -26, 0, 0, -2, -32, -38, -20, -29, -7, 0, 1, 2, 12, 15, -14, -12, -16, -16, 31, 9, -12, -1, 0, -3, -13, 20, 10, 27, -12, -18, 16, -20, -19, -36, -19, 18, 23, -11, 17, 5, -10, 0, 0, 0, -7, -8, -2, -7, -16, -12, -34, -30, -16, -28, -19, 26, -12, -4, 30, -15, -9, 0, 0, 0, -2, -16, -15, 13, -6, -21, -17, -13, -18, -23, -22, -19, -9, 7, 2, -18, 0, 0, 0, 0, 1, 9, -13, -14, -17, -14, -6, -4, -2, -5, -12, 3, 10, 3, -7, -5, 0, 0, 0, 0, 0, 5, -13, -19, -10, 0, 0, -4, 0, -1, -5, 6, 33, 37, 8, -3, 0, 0, 0, 0, 0, -1, -5, -2, -2, 8, 6, -1, 3, 0, -1, 0, 7, 23, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, -2, 0, 0, 0, 0},
	    {-52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, -1, -2, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -4, -6, -7, -4, 1, 7, 10, 0, -16, -6, 2, -5, -1, 0, 0, 0, 0, 0, 1, 1, 4, 8, 9, 1, -22, -4, 17, 3, -1, 8, -3, -4, -11, -5, 0, 0, 0, -1, 7, -3, -9, 1, -5, -31, -38, -4, 9, 16, 5, 0, 4, 10, -14, -16, 0, 0, -2, 0, 13, 5, 7, 7, -3, -44, -33, 22, 14, -2, 21, 0, 3, 21, -1, -20, 0, -1, -6, 5, 15, 0, -3, 12, 5, -40, -25, 8, 6, -9, 12, 10, -1, -17, -12, -18, -1, 0, -5, 15, 0, -6, 6, 6, -2, -30, -10, -15, 11, 0, 1, 7, 15, -13, -15, -17, -2, 0, 4, 15, -6, 7, 8, -8, 6, -19, -10, 6, 16, 11, 14, 10, 11, -2, -13, -13, -1, 0, 5, 7, 12, 1, -12, 7, -10, -29, -9, -2, 3, 2, 14, 3, 3, -1, -6, -12, -1, 1, -18, -7, 14, 5, -5, 7, -8, -10, -24, -6, 8, 3, 7, 4, -17, -3, -3, -15, 0, 4, -13, -14, 2, 6, -2, -13, 0, 5, -6, -8, 4, 6, 0, 6, -12, -8, -13, -18, -1, 1, -10, -20, 8, 6, -18, 11, -1, -16, 2, 4, -15, 8, 8, -6, 6, 12, 3, -8, -1, 0, -14, -21, -9, 10, -9, 16, -6, -20, -7, -11, 5, 0, -4, 1, 7, -7, 13, -1, -1, 0, -7, -1, -12, -1, -4, 1, 14, 6, 2, -5, 9, -9, -7, 14, 10, -14, 12, -5, 0, 0, -1, -4, -17, -7, 11, -5, 2, -3, -7, -14, -2, 11, 5, 3, 14, 5, 4, -4, 0, 0, 0, -2, -15, -16, -8, -7, -6, -20, -5, -20, -20, 21, 4, 0, 15, 11, 1, -2, 0, 0, 0, 0, 0, -8, -22, -21, 5, 10, 8, -12, 0, 16, 4, 4, 5, 1, -1, 0, 0, 0, 0, 0, 1, 0, -7, -8, 0, 11, 8, 4, 27, 19, 9, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 4, 0, 0, 0, 0, 0, 0, 0},
	    {-79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 2, -3, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 12, 11, 5, -1, -1, -2, -3, 5, 11, 5, 3, 6, 10, 0, 0, 0, 0, 0, 1, 9, 6, 6, -1, -10, -8, -8, -3, 13, 25, 23, 3, 11, 21, 3, 0, 0, 0, 0, 4, 10, 0, 9, 10, -17, -18, -15, -15, -3, -1, 17, 0, 4, 18, 1, 0, 0, 0, 0, 8, 7, -4, -1, -2, -19, -6, -14, -24, -7, -3, 7, -10, 0, 30, 2, -1, 0, 0, -1, -4, -1, -3, -9, -12, -13, -6, 9, -13, -10, -4, 4, 2, 2, 8, 2, -2, 0, 0, 0, -2, 14, -1, -4, -20, -9, -9, 1, -4, -33, -17, -11, -4, 8, -2, 5, -1, 0, 0, 2, -1, 8, -4, -7, -22, 3, 1, 4, 7, -24, -7, -9, -3, 4, 1, 2, -3, 0, 0, 9, 7, 3, 4, 9, -12, 8, 7, 3, 5, -20, -9, 1, -2, -1, 9, 4, -6, 0, 0, 1, -3, -6, 10, -8, 3, 18, 4, 0, -3, -26, -16, 2, 0, 1, 0, -9, -6, 0, -1, 5, 10, 5, -3, 13, 23, -5, 12, 3, 0, 10, 9, 3, 5, 2, -4, -15, -4, 0, 0, 14, -4, -4, 7, 0, 5, 10, 15, -9, -6, 2, -1, -5, 10, 3, -9, -12, -1, 0, 0, 10, -1, -4, 11, -6, 3, 12, -8, -5, 2, 24, 7, -1, 1, 2, 3, 2, 0, 0, 0, 3, -15, -6, 5, 9, 6, -3, -7, 1, -2, 1, -3, 4, 8, 5, -5, 3, 2, 0, 0, -1, -14, -12, -13, 9, 6, -11, -15, -3, 5, 14, 8, 13, 11, -4, 0, 3, 0, 0, 0, -1, -6, -6, -8, -6, 0, -5, -12, 0, 11, 3, -15, -14, -6, -4, 0, 1, 0, 0, 0, 0, -1, -10, -22, -21, -7, -2, -2, 0, 4, -5, -10, -8, -7, 0, 0, 0, 0, 0, 0, 0, 0, -1, -6, -5, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {-35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -7, -3, 0, 0, 0, 0, -3, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, -2, -19, -18, -4, 2, -9, -16, -14, -3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 2, 10, -4, -2, 10, 10, -8, -26, -16, -9, -7, -3, -1, 0, 0, 0, 0, -2, -8, 0, -5, -1, -11, -12, -1, 22, -2, -12, 20, -1, -26, -12, 4, -9, -2, 0, 0, -1, -8, -3, -5, 6, -4, 1, 11, 14, 8, 18, -18, -16, -23, -3, -8, -20, -4, 0, 0, -4, -4, 5, 0, -16, -9, 9, 17, 4, 11, 25, -13, -13, -14, 4, 3, -11, -2, 0, -8, -21, 0, 0, -3, 0, -2, 2, 22, -4, 2, -14, -14, -14, -9, -7, -9, -25, -1, 0, -10, -19, -5, -8, -12, -10, -3, 10, 29, 28, 17, -8, -6, -10, -24, -5, -7, -30, -2, -1, -11, -35, -20, -12, -23, -10, -11, 0, -4, -1, 0, 17, 27, -15, -11, -3, -10, -32, -5, 0, -18, -40, -5, -10, -26, -21, -38, -14, -8, -10, 6, 1, 10, 3, -7, -5, 0, -15, -11, -3, -13, -27, 6, -2, -31, 10, 0, 18, 0, 9, 28, 14, 11, 10, -18, -2, -13, -18, -6, 0, -16, -40, 2, -3, -14, -9, -2, 0, 17, 0, 0, 7, -17, -1, 6, 21, -9, -34, -5, 0, -7, -20, -15, -13, 6, -5, 0, -4, 12, 12, 10, 3, -5, -15, 1, 10, -17, -18, -1, 0, -4, -5, 14, 9, -5, -6, -6, -15, 11, -1, 1, 3, 8, -3, 5, 1, -19, -12, -1, 0, -4, 0, 12, 6, 16, -6, 6, 4, 1, 2, -5, -19, -21, -2, 11, 8, -15, -17, -7, 0, -1, 0, 5, 19, 4, -16, 2, -11, -15, 0, 10, 7, -24, -9, 7, 7, -1, 0, -2, 0, 0, 0, -3, -5, 0, -19, -8, -8, -10, -23, -14, 0, -13, -8, -3, 2, 2, 2, 0, 0, 0, 0, 0, -3, 7, 5, 1, -8, -9, -6, -16, -12, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, 0, 0, -1, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0},
	    {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 7, 11, 0, 0, 0, 0, 0, 0, 0, 0, -1, -5, -11, -14, -4, -1, 0, 0, -1, -3, 14, 22, -5, -3, 0, 0, 0, 0, 0, 0, -7, -19, -24, -15, -4, -2, -9, -11, -3, 2, 0, 0, 4, 0, 5, 0, 0, 0, 0, 0, -18, -35, -17, 0, 1, 8, 4, -14, -20, 20, 16, -21, 5, 5, -1, -1, 0, 0, 0, -1, -17, -13, -16, -19, -1, 15, 19, -14, -44, 11, 21, 7, 6, 10, -19, -11, 0, 0, 0, -4, -10, 17, 12, 11, 7, 0, 2, 3, 2, -42, -21, 21, 0, -1, 1, -10, -2, 0, 0, -8, -19, -4, -7, -16, 19, 8, 1, 6, 22, -18, -8, 18, -2, -2, 8, -10, -2, 0, -1, 0, -5, 6, 12, 20, 8, 4, 18, 0, -2, -11, -1, -6, 15, 13, 6, -8, -2, 0, -4, 3, -9, -11, 4, -23, 13, 0, 16, -4, 0, -31, 0, 0, 5, -8, -3, 2, -4, 0, -8, -12, -6, -2, 2, -7, 7, -17, -4, -14, 6, -19, 14, -18, 6, 6, 11, -4, -4, 0, -8, -21, -12, -6, -10, -9, -25, 9, -26, -1, -29, 11, -7, -15, 2, -2, 1, -7, -3, 0, -7, -28, 14, -7, -9, 8, -38, 0, -13, 2, -12, 14, 0, 11, -9, 0, -2, -6, -3, 0, -4, -22, -6, 1, -9, 3, -21, -20, -7, -5, 0, -17, 11, -12, 2, 1, -8, -13, -5, 0, -4, -6, 0, 4, 16, -1, -32, -39, 19, -12, 6, 1, 4, 9, 10, -2, -3, -16, -3, 0, -5, -5, 10, 5, 6, 17, -12, -53, 9, 0, -5, 6, 0, -9, 4, 7, -8, -17, -11, 0, 0, -2, 3, 4, 0, 3, -11, -76, -59, -15, -10, -2, 6, 21, 28, 12, -1, -2, -2, 0, 0, 3, 6, 13, 27, 62, 33, -28, -37, 3, 23, 21, 13, 13, 11, 1, -1, 0, 0, 0, 0, 0, 11, 18, 13, 45, 58, 19, 0, -4, -3, -1, 0, -8, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 1, 3, 2, 0, 0, -1, -2, 0, -1, 0, 0, 0, 0, 0},
	    {-57, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -6, -3, -5, -9, -8, -4, -1, -2, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10, -7, -2, -8, -3, 12, 10, 4, -6, -5, -4, -6, -1, 0, 0, 0, 0, 0, -1, 0, -3, 0, -2, -1, 14, 10, 15, 9, -6, -17, -9, -18, -12, -4, 0, 0, 0, 2, 4, 0, -12, -29, -14, -3, -11, 0, 17, -29, 8, -10, -27, 13, -13, -12, 0, 0, 2, 17, 14, -4, -4, -12, -4, 10, 19, 10, 13, 9, 31, 21, 2, 27, -2, -17, -1, 0, 1, 13, 3, -2, -3, -10, -21, -1, -2, 4, 11, 0, 7, 18, 7, 12, -4, -26, -1, 0, 0, 1, -9, -26, -2, -4, -10, -16, 0, 8, 6, 9, 29, 20, 16, 11, -16, -26, -1, 0, 0, 5, 5, -30, -3, -20, -2, -3, 17, -6, -2, -15, 0, 12, 15, 21, 0, -33, -4, 0, 0, 8, 13, -17, -4, -2, -12, -18, -4, -5, 34, 3, 0, 10, 8, 4, 1, -39, -7, 0, 0, -1, 7, -14, -11, -10, -10, -32, -8, -6, -8, -1, -20, 12, 11, 21, 2, -22, -3, 0, 0, 5, 7, -22, -2, -4, -34, -24, 4, -1, 0, 4, -2, 16, -5, 10, -17, -16, -2, 0, -1, 16, 17, -11, 12, -34, -41, -6, -11, -10, -8, -1, 0, 3, 0, 31, -3, -13, -2, 0, 0, 10, 14, 19, -14, -43, -3, 0, -23, 6, 15, -17, 18, -6, 1, 4, -9, -8, -1, 0, 0, 4, -18, 0, -12, -13, -21, -29, 8, 0, 24, 2, -14, -15, 5, -24, -13, -3, -1, -1, 0, 1, -27, -9, 7, -12, -17, -21, 6, 1, 15, 16, 8, 4, 0, -20, -9, -1, 0, 0, 0, 0, -20, -18, 3, -19, -39, -14, 15, 21, 11, -10, -21, -7, -13, -12, -5, 0, 0, 0, 0, 0, 0, 1, 11, -4, -11, -3, -15, -4, 17, 0, -7, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 7, -2, 0, 0, -2, -2, -3, -1, 0, 0, 0, 0, 0, 0, 0},
	    {-31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 24, 34, 22, 10, 10, 4, -1, -2, -3, -2, -2, 0, 0, 0, 0, 0, 0, -4, 3, 2, 18, 13, 12, 6, 11, 20, 1, -14, -10, -7, -1, 3, 0, 0, 0, 0, -5, -4, 18, 11, -6, -18, -10, 2, 5, 6, -21, -27, -20, -7, 7, 6, -2, 0, 0, 0, -4, 2, 13, 13, 5, 8, -19, -8, -2, 3, -30, -25, -12, 0, 17, 13, -1, 0, 0, 0, -1, 4, -5, 12, 4, 2, -16, 4, -3, -3, -28, -5, 11, -9, 3, 10, -1, 0, 0, -2, -1, 3, 0, 6, -6, -10, -6, -4, -15, -11, -13, 1, -6, -20, -2, 11, -1, 0, 0, -3, -5, -1, 6, 11, 7, -6, -26, -16, -15, 2, -1, 2, 6, -6, 7, 8, -4, 0, 0, -5, -10, -1, 7, -4, 15, 5, -35, -15, -14, -2, -2, -1, 6, -5, -13, 0, -1, 0, 0, -7, -7, -2, -7, 11, 5, 5, -23, -10, -16, 14, 2, -10, -5, -10, 19, -1, -5, 0, 0, -5, -22, 3, -2, 10, 22, 23, 4, -2, -11, 5, -13, 0, -5, 0, 4, -4, 0, 0, 0, -1, -40, -3, 8, 6, 9, 27, -6, 0, 15, -9, -1, -1, -9, -18, -6, 9, 4, 0, 0, -1, -30, -20, 0, 1, 8, 22, -15, 0, 14, 6, -7, -16, -19, -20, -12, 8, 4, 0, 0, 0, -16, -16, 3, 1, 9, 5, -2, 8, 16, -1, -17, -12, -12, -17, -16, 2, 3, 0, 0, 0, -9, -6, 2, 3, 1, 2, 13, 7, 7, -18, -12, -10, -4, -14, -8, 2, 10, 0, 0, 0, -4, -5, -4, 6, 12, -1, -6, -6, 1, -17, -17, -18, -20, -21, -11, -5, 1, 0, 0, 0, -1, -7, -12, -5, 1, -8, -14, -4, -3, -6, 5, -1, -2, -1, 0, 0, 0, 0, 0, 0, 0, -1, -6, -6, -2, 0, 0, 4, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {-128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -3, -2, 0, 0, 0, 0, -1, -4, -7, -6, -2, -1, 0, 0, 0, 0, 0, -1, -3, -11, -12, 3, 14, 9, -8, -6, -1, -1, -1, -12, -13, -8, 0, 0, 0, 0, 0, -4, -13, -18, -2, 13, 7, 0, -17, -13, -3, -9, 4, 7, -7, -10, -4, 0, 0, 0, 0, -6, -17, 1, 7, 11, 0, -6, -5, -15, 1, -8, -9, 13, -7, -6, -8, 0, 0, 0, 0, -6, -10, 0, 15, 7, 0, 0, -6, -17, 12, 13, -1, 0, -11, 1, -12, -1, 0, 0, 0, -2, -4, -5, 8, 19, 1, -8, -3, -1, 22, 10, 2, -17, 7, -2, -19, -2, 0, 0, -1, 0, 0, -9, 8, 4, 7, 16, 20, 7, 2, 14, 1, -17, 19, -6, -18, -3, 0, 0, -3, -4, 18, -3, 0, 14, 23, 2, 4, 16, 7, 1, -10, 9, 19, 2, -18, -5, 0, -1, -8, 1, 14, -9, -8, -20, 1, 12, -1, 5, 4, -18, -14, 3, -6, 12, -13, -3, 0, -2, -10, 0, 4, 0, -1, -9, -2, 27, 12, 10, 3, 4, -9, -7, -3, 17, -11, -1, 0, -2, -16, 3, 13, -12, 5, 1, -11, -17, 6, -13, -2, -10, -6, 10, -1, 8, -8, 0, 0, -2, -9, 5, -7, 0, -2, 1, 14, -10, -11, -9, -15, -9, 2, 2, 4, 9, -1, 0, 0, 0, -9, 0, 0, -2, 4, 13, 16, -1, -18, 9, -4, -13, -2, -12, -2, 6, -1, 0, 0, 0, -4, 2, 4, -7, -2, 10, 2, 8, -13, -9, -1, 0, 8, 0, 7, 1, -2, 0, 0, 0, -2, -6, 1, 7, 20, 21, 9, 5, -2, -7, -8, 4, 6, 4, 2, -2, -1, 0, 0, 0, 0, -1, -5, -6, 1, 0, 8, -4, -1, 3, 0, -2, -1, -2, -1, 0, 0, 0, 0, 0, 0, 0, -4, -11, -12, -6, -1, 0, -1, -4, -3, -3, -3, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {-67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, -8, -13, -4, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -6, -9, -10, -5, 0, 0, 3, -1, -10, -9, -5, -2, 0, 0, 0, 0, 0, 0, -1, -7, -12, -9, 6, 23, 12, -3, 0, 0, -10, -9, -9, -9, 0, 0, -1, 0, 0, 0, -3, -14, -10, -4, 1, 11, 13, 1, -9, -3, -1, -3, -4, -5, -1, 0, -1, 0, 0, 0, -5, -15, -7, -4, -5, 7, 10, -1, -3, 5, 0, -14, -6, -3, -5, 4, 0, 0, 0, 0, -6, -2, 5, -6, 6, 17, 6, 0, 6, 4, -1, -16, -6, -13, -6, 0, -5, 0, 0, -1, 1, 10, 2, -4, 1, 5, 2, -3, 1, 0, -1, -15, -8, -10, -6, 3, -7, 0, 0, -3, -5, 9, 11, 4, -6, -5, 4, 6, -2, 0, -4, -12, -3, -8, -10, 5, -6, 0, -1, -4, -15, 8, 30, 12, 4, -2, 6, 3, -14, 1, -4, -13, -4, -11, -15, 9, 0, 0, -1, -6, -22, 7, 28, -3, -7, 4, 6, 13, 12, -1, -2, -9, -7, -14, -2, 1, -2, 0, -1, -9, -27, 10, 13, -5, -2, 12, 1, 8, 0, 0, 3, -13, -11, -11, 2, 16, -1, 0, -1, -6, -21, 4, -1, -8, 6, 3, 8, -4, -10, 2, -4, -2, -5, -14, -1, 15, 2, 0, 0, -3, -16, -4, 8, -5, -2, 17, 11, 3, -10, -4, 4, 1, -5, -4, 7, 13, 2, 0, 0, 0, -11, -19, 0, -7, 0, 11, 7, 3, -10, -15, -8, -6, -6, 0, 12, 13, 0, 0, 0, 0, -5, -18, -17, -19, -7, 0, -5, -8, -12, -13, -6, 0, 1, 2, 9, 6, 0, 0, 0, 0, -2, -7, -15, -15, -7, -1, -6, -9, -10, -9, -2, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, -1, -8, -6, -2, -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {-98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, -4, -4, -6, -8, -6, -11, -6, 1, 0, -1, 0, 0, 0, 0, 0, -1, -3, -4, -8, -7, -4, 1, 6, -1, -1, -6, -3, 11, 4, 0, 0, 0, 0, 0, 0, -3, -6, -4, -6, -4, 10, 17, 25, 7, 9, 11, -5, 11, 16, 1, -3, 0, 0, 0, 0, -5, -10, -6, -17, -6, 5, 2, 15, 26, 7, 22, 3, -8, -21, -10, -5, 0, 0, 0, -5, -13, -15, -4, -18, 2, -3, 0, 1, 13, 4, 0, 1, 0, 2, -15, -11, 0, 0, 0, -14, -16, 2, 12, -6, 1, 5, 11, 17, 0, 17, -1, 32, 12, 29, -3, -22, -3, 0, 0, -21, -6, -1, -3, -11, -1, 6, -7, 18, 16, 19, 12, 27, 4, 22, 2, -16, -5, 0, -2, -12, 8, 4, 11, 9, 3, -11, -18, 8, -34, -40, -28, 0, -12, 24, -2, -8, -4, 0, -2, 0, 8, -3, 9, 11, -1, -14, -34, -56, -65, -24, -19, -27, 5, 10, -7, -17, -1, 0, -6, -13, 3, 9, 5, -5, -9, -13, -36, -35, -5, -10, -5, -14, 1, -12, -10, -13, 0, 0, -11, -8, 0, -3, 20, 0, 16, 10, 0, 3, -11, -2, -6, -12, -29, -7, -4, -5, 0, 0, -5, -3, 3, -4, 15, 16, 23, 13, -14, -12, -4, 4, 0, -13, -21, 3, -6, -4, 0, 0, -1, -6, -1, 17, 5, -20, 4, 16, -5, -3, 7, -6, 0, -19, -5, 0, -16, -6, 0, 0, 0, -11, -9, 12, -9, 0, 19, 12, -6, 0, -7, 7, 13, -8, 4, -5, -10, -6, -2, 0, 0, -2, 0, -1, -8, 0, 16, 12, 10, 23, 9, 0, -21, -19, -14, -9, -2, -3, -1, 0, 0, 1, 5, -12, -14, -1, 1, 0, 7, 13, 7, -9, -15, -16, -12, -6, 0, 0, 0, 0, 0, 0, 0, -11, -12, -5, -1, 0, -2, -2, -4, -6, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

    ap_axis<32,2,5,6> tmp;

    static int sum = 0;
    static int res[10] = {1,2,3,4,5,6,7,8,9,10};
    static int col = 0;

    static int COL_SIZE = 10;

    while (1){
    	A.read(tmp);
    	for (int row = 0; row < COL_SIZE; row++) {
    		res[col] = res[col] + weights[row][col] * tmp.data.to_int();
    	}
    	col++;
    	if (tmp.last) {
    		break;
    	}
    }

    for(int i = 0; i < 10; i++) {
    	if(i == 9) {
    		tmp.last = 1;
    	} else {
    		tmp.last = 0;
    	}
		tmp.data = res[i];
		B.write(tmp);
    }


}
