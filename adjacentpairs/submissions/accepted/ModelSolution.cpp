#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int>  a(n);
        for(int& i : a) cin >> i, --i;
        int ans=n; // just change the numbers to the pattern 10**9-1, 10**9 ...
        array<vi,2> cnt = {vi(n),vi(n)};
        for(int i=0;i<n;++i) {
            cnt[i%2][a[i]]++;
        }
        // handle case where one of the two distinct is 10**9
        for(int rep=0;rep<2;++rep) {
            ans = min(ans,n- *max_element(all(cnt[rep])));
        }

        vi ord(n);
        iota(all(ord),0);
        sort(all(ord),[&](int i,int j) {return cnt[1][i]>cnt[1][j];});

        // handle case where both are in the array
        map<pi,int> cost; // cost for if pair (c,d) is used (with a on the even parities (0,2,4,6), b on the odd parities (1,3,5))
        for(int i=0;i+1<n;) {
            int c = a[i], d = a[i+1];
            if(i%2==0) swap(c,d);
            int j=i+2;
            while(j<n and a[j]==a[j-2]) ++j;
            cost[{c,d}]+=(j-i)/2;
            i=j-1;
        }
        vi evenCnt(n);
        for(int i=0;i<n;i+=2) evenCnt[a[i]]++;
        for(int c=0;c<n;++c) {
            for(auto d : ord) if(c!=d) {
                int cur = n-cnt[0][c]-cnt[1][d];
                if(!cost.count({c,d})) {
                    ans = min(ans,cur);
                    break;
                } else {
                    ans = min(ans,cur+cost[{c,d}]);
                }
            }
            // the second for loop runs only O(n) times total (the number of pairs in the cost map + n iterations)
        }
        cout << ans << '\n';
    }
}