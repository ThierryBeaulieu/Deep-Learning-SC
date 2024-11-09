#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

void example(hls::stream<ap_axis<32, 2, 5, 6>> &A, hls::stream<ap_axis<32, 2, 5, 6>> &B);

int main(){
    hls::stream<ap_axis<32, 2, 5, 6>> A, B;
    ap_axis<32, 2, 5, 6> tmp1, tmp2;
    //vector<int> expected_res = {5, 9, 247};
    vector<int> expected_res = {1, 2, 3, 4, 5, 6, 7, 8, };

    for (int j = 0; j < 10; j++)
    {
    	tmp1.data = expected_res[j];
        tmp1.keep = 1;
        tmp1.strb = 1;
        tmp1.user = 1;

        if (j = 9) {
            tmp1.last = 1;
        } else {
            tmp1.last = 0;
        }

        tmp1.id = 0;
        tmp1.dest = 1;
        A.write(tmp1);
    }

	example(A, B);

    while(!B.empty()) {
		B.read(tmp2);
		cout << "Received ";
		cout << tmp2.data << endl;
		if (tmp2.data.to_int() == 0){
			cout << "Expected : ";
			return 1;
		}
    }
    cout << "Success: results match" << endl;
    return 0;
}
