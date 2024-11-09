#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include <vector>

void example(hls::stream<ap_axis<32,2,5,6>> &A, hls::stream<ap_axis<32,2,5,6>> &B)
{
#pragma HLS INTERFACE axis port=A
#pragma HLS INTERFACE axis port=B
#pragma HLS INTERFACE s_axilite port=return

    ap_axis<32,2,5,6> tmp;

    std::vector<ap_axis<32,2,5,6>> something(10);

    bool sending = false;

    while(1) {
    	if (!sending) {
    		A.read(tmp);
            if (tmp.last) {
                sending = true;
            }
    	}

    	if (sending) {
        	tmp.data = tmp.data.to_int() + 5;
        	B.write(tmp);
        	break;
    	}

    }
}
