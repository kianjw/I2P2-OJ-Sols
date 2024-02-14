#define max 100000
#define maxbit 5
istream& operator>>(istream&in, BigInt&b){
    string ch;
	in>>ch;
	if(ch[0] == '-') ch = ch.substr(1, ch.length() -1), b.sign = -1;
	else b.sign = 1;
	reverse(ch.begin(),ch.end());
	int id = 0;
	for(int i = 0;i<ch.length(); i+= maxbit){
		string sub = ch.substr(i,maxbit);
		reverse(sub.begin(), sub.end());
		b[id++] = stoi(sub);
	}
	b.l = id;
	return in;
}
ostream& operator<<(ostream& out, BigInt b){
	out << ((b.sign == -1) ? "-" : "");
	out<< b[b.l-1];
	for(int i = b.l - 2; i>=0;i--){
		out.width(maxbit);
		out.fill('0');
		out<<b[i];
	}
	return out;
}


BigInt BigInt ::operator +( const BigInt &y ){
	BigInt x(*this);
	int i; long long h;
	for(i = 0, h= 0; i<x.l || i<y.l || h;i++){
		h += (i<x.l) * x[i] *x.sign + (i<y.l) * y[i] * y.sign;
		x[i] = h % max;
		h/=max;
	}
	x.l =i;
	for(;x.l>1 && !x[x.l-1]; x.l--);
	x.sign = (x[x.l-1] >= 0) ? 1 : -1;
	if(x[x.l-1] >= 0){
		for(int i = 0; i<x.l;i++){
			if(x[i]< 0){
				x[i+1]--;
				x[i]+=max;
			}
		}
	}
	else{
		for(int i = 0;i<x.l;i++){
			if(x[i] >0){
				x[i+1]++;
				x[i]-=max;
			}
		}
	}
	for(int i = 0; i< x.l;i++) x[i] *= x.sign;
	for(;x.l>1 && !x[x.l-1]; x.l--);
	if(x.sign == -1 && x.l == 1 && x[0] == 0) x.sign = 1;
	return x;

}  
BigInt BigInt ::operator -( const BigInt &y ){
	BigInt x(*this);
	int i; long long h;
	for(i = 0, h= 0; i<x.l || i<y.l || h;i++){
		h += (i<x.l) * x[i] *x.sign - (i<y.l) * y[i] * y.sign;
		x[i] = h % max;
		h/=max;
	}
	x.l =i;
	for(;x.l>1 && !x[x.l-1]; x.l--);
	x.sign = (x[x.l-1] >= 0) ? 1 : -1;
	if(x[x.l-1] >= 0){
		for(int i = 0; i<x.l;i++){
			if(x[i]< 0){
				x[i+1]--;
				x[i]+=max;
			}
		}
	}
	else{
		for(int i = 0;i<x.l;i++){
			if(x[i] >0){
				x[i+1]++;
				x[i]-=max;
			}
		}
	}
	for(int i = 0; i< x.l;i++) x[i] *= x.sign;
	for(;x.l>1 && !x[x.l-1]; x.l--);
	if(x.sign == -1 && x.l == 1 && x[0] == 0) x.sign = 1;
	return x;

} 