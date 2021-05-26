#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(){
    int S = 0;
    int M = 0;
    int N = 0;
    cin >> S;
    cin >> M;
    cin >> N;
    cin.get();
    string line;
	getline(cin, line);
	stringstream ss(line);
	vector<int> nums;
	int x;
    int max = 0;
	while (ss >> x){
		nums.push_back(x);
        if (x >= max){
            max = x;
        }}
    
    sort(nums.begin(),nums.end());
    int target = 0;
    for (int i = 0; i < N; i++)
    {
        if (nums[i] <= S)
        {
            target = i;
        }
        else
        {
            break;
        }    
    }

    int sum = 0;
    vector<int> out;
    int tmp = S;
    for (int i = target; i >= 0; i--)
    {
        sum += abs(tmp - nums[i]);
        out.push_back(nums[i]);
        tmp = nums[i];
    }
    sum += abs(max - tmp);
    tmp = max;
    for (int i = N -1; i > target; i--)
    {
        sum += abs(tmp - nums[i]);
        out.push_back(nums[i]);
        tmp = nums[i];
    }
    printf("%d ", S);
    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
        {
            printf("%d\n", out[i]);
        }
        else{
            printf("%d ", out[i]);
        }
        
    }
    printf("%d\n", sum);
    
    return 0;
}