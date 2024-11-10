#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

void example(hls::stream<ap_axis<32, 2, 5, 6>> &A, hls::stream<ap_axis<32, 2, 5, 6>> &B);

int main(){
    hls::stream<ap_axis<32, 2, 5, 6>> A, B;
    ap_axis<32, 2, 5, 6> tmp1, tmp2;
    //vector<int> expected_res = {5, 9, 247};
    vector<int> expected_res = {9, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (int k = 0; k < 3; k++){

		for (int j = 0; j < 10; j++)
		{
			tmp1.data = 1;
			tmp1.keep = 1;
			tmp1.strb = 1;
			tmp1.user = 1;
			tmp1.id = 0;
			tmp1.dest = 1;

			if (j == 9) {
				tmp1.last = 1;
			} else {
				tmp1.last = 0;
			}

			A.write(tmp1);
			example(A, B);
		}



		for (int i = 0; i < 10; i++) {
			example(A, B);
			B.read(tmp2);
			if (tmp2.data.to_int() != expected_res[i]){
				cout << "Failure: results doesn't match" << endl;
				return 1;
			}
		}
	}
    cout << "Success: results match" << endl;
    return 0;
}
