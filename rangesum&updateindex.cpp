#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int build(vector<int> &segtree,int l,int r,vector<int> &arr,int i)
{
    if(l==r)
    {
        segtree[i]=arr[l];
        return segtree[i];
    }
    int mid=(l+r)/2;
    segtree[i]=build(segtree,l,mid,arr,2*i+1)+build(segtree,mid+1,r,arr,2*i+2);
    return segtree[i];
}
void build_t(vector<int> &segtree,int s,vector<int> &arr,int n)
{
    build(segtree,0,n-1,arr,0);
}
void update_util(vector<int> &segtree,int l,int h,int newv,int index,int i)
{
    if(index>=l && index<=h)
    {
        segtree[i]+=newv;
        if(l==h)
        return;
        int mid=(l+h)/2;
        update_util(segtree,l,mid,newv,i,2*i+1);
        update_util(segtree,mid+1,h,newv,i,2*i+2);
    }
    return;
}
void update(vector<int> &segtree,int n,int newv,int i)
{
    update_util(segtree,0,n-1,newv,i,0);
}
int ranges(vector<int> &segtree,int sl,int sr,int ql,int qr,int i)
{
    if(qr<sl ||sr<ql)
    {
        return 0;
    }
    else if(ql<=sl && sr<=qr)
    {
        return segtree[i];
    }
    else{
        int mid=(sl+sr)/2;
        return ranges(segtree,sl,mid,ql,qr,2*i+1)+ranges(segtree,mid+1,sr,ql,qr,2*i+2);
    }

}
void print(vector<int> &segtree,int s)
{
    for(int i=0;i<s;i++)
    {
        cout<<segtree[i]<<" ";
    }
}
int main()
{
    int n;
    cout<<"Enter no of Element: ";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter Elements: ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    size_t s=pow(2,ceil(log2(n)+1))-1;
    vector<int> segtree(s,0);
    build_t(segtree,s,arr,n);
    cout<<"Tree: ";
    print(segtree,s);
    cout<<endl;
    int choice;
    int l,r,index,val,ch;
    cout<<"Enter the no. of Choice: ";
    cin>>choice;
    while(choice--)
    {
        cout<<endl;
        cout<<"1 for update"<<endl<<"2 for rangesum "<<endl;
        cout<<"Enter Your Choice: ";

        cin>>ch;
        if(ch==1)
        {
            cout<<"Enter the Index And Value: ";
            cin>>index>>val;
            int newv=abs(val-arr[index]);
            update(segtree,n,newv,index);
            print(segtree,s);
        }
        else if(ch==2)
        {
            cout<<"Enter the range: ";
            cin>>l>>r;
            cout<<ranges(segtree,0,n-1,l,r,0);
        }
    }
}
