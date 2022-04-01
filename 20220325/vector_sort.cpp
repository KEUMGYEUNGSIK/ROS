#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    int n;
 
    cin >> n;
    
    vector <vector<int>> time(n,vector<int>(2,0)); // n행 2열을 가지는 벡터 선언
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> time[i][j];
        }
    } // 테스트를 위한 임의의 값 배정
 
    cout << endl;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cout << time[i][j] << " ";
        }
        cout << endl;
    } // 출력
 
    sort(time.begin(), time.end()); // 기준 함수를 정해주지 않음
 
    cout << "정렬 후 값 : " << endl;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cout << time[i][j] << " ";
        }
        cout << endl;
    } // 정렬 된 후 값 출력
 
    return 0;
}
