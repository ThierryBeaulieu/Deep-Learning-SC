#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

void example(hls::stream<ap_axis<32, 2, 5, 6>> &A, hls::stream<ap_axis<32, 2, 5, 6>> &B);

int main(){
    int i = 100;
    hls::stream<ap_axis<32, 2, 5, 6>> A, B;
    ap_axis<32, 2, 5, 6> tmp1, tmp2;

    for (int j = 0; j < 100; j++){

    	tmp1.data = i;
        tmp1.keep = 1;
        tmp1.strb = 1;
        tmp1.user = 1;

        if (j = 99) {
            tmp1.last = 1;
        } else {
            tmp1.last = 0;
        }

        tmp1.id = 0;
        tmp1.dest = 1;
        A.write(tmp1);
        example(A, B);
        B.read(tmp2);

        if (tmp2.data.to_int() != 105) {
            cout << "Error: result mismatch" << endl;
            return 1;
        }
    }
    cout << "Success: results match" << endl;
    return 0;
}
