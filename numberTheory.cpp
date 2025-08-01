
struct numbertheory{
    int n;
    vector<int> spf;
    numbertheory(int x) : n(x), spf(n+1,-1){
        build();
    }

    void build(){
        spf[1]=1;
        for(int i=2;i<=n;i++){
            if(spf[i]!=-1) continue;
            for(int j=1;i*j<=n;j++){
                spf[i*j]=i;
            }
        }
    }

    map<int,int> factorise(int x){
        map<int,int> mp;
        int z=x;
        while(z>1){
            mp[spf[z]]++;
            z/=spf[z];
        }
        if(z>1) mp[z]++;
        return mp;
    }

    bool isPrime(int n){
        if(n==1) return false;
        if(spf[n]==n) return true;
        return false;
    }

    set<int> getFactors(int z){
        set<int> sol;
        sol.insert(1);
        sol.insert(z);
        for(int i=2;i*i<=z;i++){
            if(z%i==0){
                sol.insert(i);
                sol.insert(z/i);
            }
        }
        return sol;
    }
};
