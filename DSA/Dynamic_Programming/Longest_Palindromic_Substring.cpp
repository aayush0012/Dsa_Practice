class Solution {
public:
int solve(vector<vector<int>> &dp,int i ,int j , string &s,string&s2){
    if(i<0||j<0)return 0; 
    if(dp[i][j]!=-1)return dp[i][j]; 
    if(s[i]==s2[j]){
        dp[i][j] = 1+solve(dp,i-1,j-1,s,s2); 
    }
    else{
        dp[i][j]= max(solve(dp,i-1,j,s,s2),solve(dp,i,j-1,s,s2)); 
    }
    return dp[i][j]; 
}
    int longestPalindromeSubseq(string s) {
        string s2 = s;
        reverse(s2.begin(),s2.end());  
        int n =s.length(); 
        vector<vector<int>>dp(n,vector<int>(n,-1)); 
        int ans=solve(dp,n-1,n-1,s,s2); 
        return ans; 
    }
};
