#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

void example(hls::stream<ap_axis<32, 2, 5, 6>> &A, hls::stream<ap_axis<32, 2, 5, 6>> &B);

int main(){
    hls::stream<ap_axis<32, 2, 5, 6>> A, B;
    ap_axis<32, 2, 5, 6> tmp1, tmp2;
    // vector<int> expected_res = {5, 9, 247};
    vector<int> expected_res = {0, 1, 2};

    for (int j = 0; j < 3; j++)
    {
    	tmp1.data = j;
        tmp1.keep = 1;
        tmp1.strb = 1;
        tmp1.user = 1;

        if (j = 2) {
            tmp1.last = 1;
        } else {
            tmp1.last = 0;
        }

        tmp1.id = 0;
        tmp1.dest = 1;
        A.write(tmp1);
        example(A, B);
    }

    for (int i = 0; i < 3; i++) {
		B.read(tmp2);
		if (tmp2.data.to_int() != expected_res[i]){
			cout << "Index ";
			cout << i << endl;
			cout << "Received ";
			cout << tmp2.data.to_int() << endl;
			cout << "Expected : ";
			cout << expected_res[i] << endl;
			return 1;
		}
    }
    cout << "Success: results match" << endl;
    return 0;
}
