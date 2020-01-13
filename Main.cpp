#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;


bool labitchanle(string str){
	for (int i = 0; i < str.size(); ++i)
	{
		if(char(str[i]) != '0' && char(str[i]) != '1'){
			return true;
		}
	}
	return false;
}

bool *stob(string str){
	bool *v = new bool[str.size()];
	for (int i = 0; i < str.size(); ++i)
	{
		if(char(str[i])=='0'){
			v[i] = false;
		}
		else{
			v[i] = true;
		}
	}
	return v;
}

bool* congbit(bool* list1, bool* list2,int N){
	for (int i=0; i<N ; i++){
		list1[i] = list1[i]^list2[i];
	}
	return list1;
}

bool* dichtrai(bool* list, int N){
	int tmp = list[N-1];
	for(int i=0; i<N ;i++){
		//cout<<N-1-i<<endl;
		
		list[N-1-i] = list[N-1-i-1];
		if(N-1-i==0) {
			list[0] = tmp;
		}
		
	}
	return list;
}

bool* dichphai(bool* list, int N){
	int tmp = list[0];
	for(int i = 0 ; i<N ; i++){		
		
		if(i==N-1) {
			list[N-1]=tmp;
			break;
		}
		list[i] = list[i+1];
		

	}
	return list;
}

int check(bool *list1,int n){
	int counter=0;
	for (int i = 0; i < n; ++i)
	{
		if(list1[i]==1){
			counter+=1;;
		}
		else{
			continue;
		}
	}
	return counter;
}

bool* chia(bool* list1, int n, bool* list2, int k,bool* thuong11 ){

	int i;
	bool *thuong = new bool[n-k+1];
	for (int i = 0; i < n; ++i)
	{
		thuong11[i] = list1[i];
	}
	for ( i = 0; i<=n-k;i++){
		if (thuong11[i]==1){
			congbit(&thuong11[i],list2,k);
			thuong[i] = 1;
		}
		else{
			thuong[i] = 0;
			
		}
		
	}
	
	return thuong;
	
}

bool* decode(bool* list1, int n, bool* list2, int k){
	bool* du = new bool[n];
	for (int j = 0; j < n; ++j){
		du[j] = list1[j];
	}
	chia(list1,n,list2,k,du);
	int i;
	
	for (i = 0; i <= n; ++i)
	{
		if(i==n){
			return NULL;
		}
		if(check(du,n) <= int((((n*pow(2,k-1))/(pow(2,k)-1)) - 1)/2)){
			break;
		}
		if(check(du,n) > int((((n*pow(2,k-1))/(pow(2,k)-1)) - 1)/2)){ /////// D0 (((n*pow(2,k-1))/(pow(2,k)-1)) - 1)/2)
			dichphai(list1,n);
			chia(list1,n,list2,k,du);
		}
		
	}
	congbit(list1,du,n);
	for (int j = 0; j < i; ++j){
		dichtrai(list1,n);
	}
	return list1;
}

bool *Giaima(string str_ma,string str_ham){
	string code = str_ma, ham = str_ham;
	int leng_code = code.size();
	int leng_ham = ham.size();
	bool *unchanged_code = new bool[leng_code];
	bool *copy_code = new bool[leng_code];
	bool *copy_ham = new bool[leng_ham];
	unchanged_code = stob(code);
	copy_code = stob(code);
	copy_ham = stob(ham);
	cout<<"Mã đúng : ";
	bool *result = new bool[leng_code];
	result = decode(copy_code,leng_code,copy_ham,leng_ham);
	for (int i = 0; i < leng_code; ++i)
	{
		cout<<result[i];
	}
	cout<<endl;
	if(result==NULL){
		cout<<"Khong the tim duoc tin nhan "<<endl;
		return NULL;
	}
	for (int i = 0; i < leng_code; ++i)
	{
		if(unchanged_code[i]!=result[i]){
			cout<<"Lỗi ở vị trí : "<<i<<endl;
		}
	}
	bool *ketqua1 = new bool[leng_code];
	bool *ketqua = new bool[leng_code-leng_ham+1];
	ketqua = chia(result,leng_code,copy_ham,leng_ham,ketqua1);
	cout<<"Tu ma la : ";
	for (int i = 0; i < leng_code-leng_ham+1; ++i)
	{
		cout<<ketqua[i];
	}
	cout<<endl;
	
	return result;
}


bool *GiaimaHT(string str_ma, string str_ham){
	string code = str_ma, ham = str_ham;
	int leng_code = code.size();
	int leng_ham = ham.size();
	bool *unchanged_code = new bool[leng_code];
	bool *copy_code = new bool[leng_code];
	bool *copy_ham = new bool[leng_ham];
	unchanged_code = stob(code);
	copy_code = stob(code);
	copy_ham = stob(ham);
	cout<<"Mã đúng : ";
	bool *result = new bool[leng_code];
	result = decode(copy_code,leng_code,copy_ham,leng_ham);
	if(result == NULL){
		cout<<"Khong the tim duoc loi!"<<endl;
		return NULL;
	}
	for (int i = 0; i < leng_code; ++i)
	{
		cout<<result[i];
	}
	cout<<endl;
	for (int i = 0; i < leng_code; ++i)
	{
		if(unchanged_code[i]!=result[i]){
			cout<<"Lỗi ở vị trí : "<<i<<endl;
		}
	}
	cout<<"Tu ma la : ";
	for (int i = 0; i < leng_code-leng_ham+1; ++i)
	{
		cout<<result[i];
	}
	cout<<endl;
	
	return result;

}


bool *MahoaHT(string MSG, string CRC){
	string msg = MSG,crc = CRC;
	int m = msg.length(), n=crc.length();
	for (int i = 1; i <= n-1; ++i)
	{
		msg+='0';
	}
	bool *b_tin = new bool[m+n-1];
	bool *b_ham = new bool[n];
	bool *b_tmp = new bool[m+n-1];
	bool *b_ketqua = new bool[m+n-1];
	b_tin = stob(msg);
	b_ham = stob(crc);
	for (int i = 0; i < m+n-1; ++i)
	{
		b_ketqua[i] = b_tin[i];
	}
	chia(b_tin,m+n-1,b_ham,n,b_tmp);
	congbit(b_ketqua,b_tmp,m+n-1);
	cout<<"Tu ma : ";
	for (int i = 0; i < m+n-1; ++i)
	{
		cout<<b_ketqua[i];
	}
	cout<<endl;
	return b_ketqua;

}


bool* Mahoa(string tin, string ham){
	string str_list1 = tin ,str_list2 = ham;
	int leng_l1 = str_list1.size();
	int leng_l2 = str_list2.size();
	bool *list1 = new bool[leng_l1];
	bool *list2 = new bool[leng_l2];
	bool *list = new bool[leng_l1+leng_l2 -1 ];
	list1 = stob(str_list1);
	list2 = stob(str_list2);
	for (int i = 0; i < leng_l1+leng_l2;i++){
		list[i] = 0;
	}
	
	for (int i=0; i < leng_l1;i++){
		if(list1[i]==1) {
			int tmp = i;
			for (int j = 0; j<leng_l2; j++)
				list[tmp+j] = list[tmp+j]^list2[j];

		}
		else
			continue;
	}
	cout<<"Ma : ";
	for (int i = 0; i < leng_l1+leng_l2-1; ++i)
	{
		cout<<list[i];
	}
	cout<<endl;
	
	return list;
}

bool kiemtraloidaco(std::vector<int> v_random, int i_random){
	for (int i = 0; i < v_random.size(); ++i)
	{
		if(i_random==v_random[i]){
			return true;
		}
	}
	return false;
}

bool *Loingaunghien(bool *code, int n, int k){
	int i_loi = 0;
	cout<<"Nhap so loi : ";
	cin>>i_loi;
	cin.ignore(256,'\n');
	std::vector<int> v_random;
	for (int i = 0; i < i_loi; ++i)
	{
		
		int i_random = rand() % (n);
		if(kiemtraloidaco(v_random,i_random)){
			i_loi += 1;
			continue;
		}
		code[i_random] = !code[i_random];
		v_random.push_back(i_random);
	}
	for (int i = 0; i < v_random.size(); ++i)
	{
		cout<<"Loi o vi tri : "<<v_random[i]<<endl;
	}
	return code;

}

void Process1(){
	cout<<"1. x^3 + x + 1. CRC-3-GSM. For mobile networks"<<endl;
	cout<<"2. x^7 + x^3 + 1. CRC-7 For telecom systems"<<endl;
	cout<<"3. x^16 + x^15 + x^2 + 1. CRC-16-IBM."<<endl;
L0:
	cout<<"chon hàm  : "; 
	int i_luachon;
	string s_ham;
	cin>>i_luachon;
	cin.clear();
	cin.ignore(256,'\n');
	if(i_luachon == 1){
		s_ham = "1011";
	}
	else if(i_luachon == 2){
		s_ham = "10001001";
	}
	else if(i_luachon == 3){
		s_ham = "11000000000000101";
	}
	else{
		goto L0;
	}

L1:
	cout<<"Nhap tin : ";
	string s_tin;
	getline(cin,s_tin);
	if(labitchanle(s_tin)){
		goto L1;
	}
	bool *b_bitnhan = new bool[s_tin.size()+s_ham.size()-1];
	b_bitnhan = Loingaunghien(MahoaHT(s_tin,s_ham), s_tin.size() + s_ham.size()-1, s_ham.size());
	cout<<"Tu ma nhan duoc: ";
	for (int i = 0; i < s_tin.size()+s_ham.size()-1; ++i)
	{
		cout<<b_bitnhan[i];
	}
	cout<<endl;
	string s_bitnhan = "";
	for (int i = 0; i <s_tin.size()+s_ham.size()-1 ; ++i)
	{
		if(b_bitnhan[i]==true){
			s_bitnhan += "1";
		}
		else{
			s_bitnhan += "0";
		}
	}
	bool *b_tin = new bool[s_tin.size() + s_ham.size()-1];
	b_tin = GiaimaHT(s_bitnhan,s_ham);


		
}

void Process2(){
	cout<<"1. x^3 + x + 1. CRC-3-GSM. For mobile networks"<<endl;
	cout<<"2. x^7 + x^3 + 1. CRC-7 For telecom systems"<<endl;
	cout<<"3. x^16 + x^15 + x^2 + 1. CRC-16-IBM."<<endl;
L0:
	int i_luachon;
	cout<<"chon hàm  : "; 
	string s_ham;
	cin>>i_luachon;
	cin.clear();
	cin.ignore(256,'\n');
	if(i_luachon == 1){
		s_ham = "1011";
	}
	else if(i_luachon == 2){
		s_ham = "10001001";
	}
	else if(i_luachon == 3){
		s_ham = "11000000000000101";
	}
	else{
		goto L0;
	}

L1:
	cout<<"Nhap tin : ";
	string s_tin;
	getline(cin,s_tin);
	if(labitchanle(s_tin)){
		goto L1;
	}
	bool *b_bitnhan = new bool[s_tin.size()+s_ham.size()-1];
	b_bitnhan = Loingaunghien(Mahoa(s_tin,s_ham), s_tin.size() + s_ham.size()-1, s_ham.size());
	cout<<"Tu ma nhan duoc : ";
	for (int i = 0; i < s_tin.size()+s_ham.size()-1; ++i)
	{
		cout<<b_bitnhan[i];
	}
	cout<<endl;
	string s_bitnhan = "";
	for (int i = 0; i <s_tin.size()+s_ham.size()-1 ; ++i)
	{
		if(b_bitnhan[i]==true){
			s_bitnhan += "1";
		}
		else{
			s_bitnhan += "0";
		}
	}
	bool *b_tin = new bool[s_tin.size() + s_ham.size()-1];
	b_tin = Giaima(s_bitnhan,s_ham);

}


int main(int argc, char const *argv[])
{

BACK:
	int luachon;
	cout<<"1. Mã hóa && Giải mã HT"<<endl;
	cout<<"2. Mã hóa && Giải mã khong HT"<<endl;
	cout<<"3. Thoát"<<endl;
	cout<<"Nhập lựa chọn : "; cin>>luachon;
	cin.ignore(256,'\n');
	if(luachon==1){
		Process1();
		goto BACK;
	}
	else if(luachon==2){
		Process2();
		goto BACK;
	}
	else if(luachon == 3){
		return 0;
	}
	else{
		goto BACK;
	}

	return 0;
}
