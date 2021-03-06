#include "BN12_for_raspi_header.h"

unsigned long int num;
/*============================================================================*/
/* main                                                                       */
/*============================================================================*/
void main(){
	init_parameters();
	set_parameters();
	print_parameters();
	
	//test_ate_pairing();	//ate,opt-ate,x-ate
	//test_G1_SCM();
	//test_G2_SCM();
	//test_G3_pow();
	test_for_RaspberryPi();
	
	
	clear_parameters();
}
/*============================================================================*/
/* time                                                                       */
/*============================================================================*/
float timedifference_msec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}
float timedifference_usec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
}

/*============================================================================*/
/* Fp                                                                         */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void Fp_init(struct Fp *P){
	mpz_init(P->x0);
}
/*---------------------------------set----------------------------------*/
void Fp_set(struct Fp *P,struct Fp *A){
	mpz_set(P->x0,A->x0);
}
void Fp_set_ui(struct Fp *P,unsigned long int a){
	mpz_set_ui(P->x0,a);
}
void Fp_set_mpz(struct Fp *P,mpz_t a){
	mpz_set(P->x0,a);
}
void Fp_set_neg(struct Fp *P,struct Fp *A){
	mpz_sub(P->x0,prime,A->x0);
}
/*---------------------------------random--------------------------------*/
void Fp_random(struct Fp *P,gmp_randstate_t state){
	mpz_urandomm(P->x0,state,prime);
}
/*---------------------------------clear---------------------------------*/
void Fp_clear(struct Fp *P){
	mpz_clear(P->x0);
}
/*---------------------------------print---------------------------------*/
void Fp_printf(struct Fp *P,char *name){
	printf("%s",name);
	mpz_out_str(stdout,10,P->x0);
}
/*---------------------------vector calculation--------------------------*/
void Fp_mul(struct Fp *ANS,struct Fp *A,struct Fp *B){
	num++;
	mpz_mul(ANS->x0,A->x0,B->x0);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_mul_ui(struct Fp *ANS,struct Fp *A,unsigned long int a){
	mpz_mul_ui(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_mul_mpz(struct Fp *ANS,struct Fp *A,mpz_t a){
	mpz_mul(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_mul_basis(struct Fp *ANS,struct Fp *A){
	mpz_sub(ANS->x0,prime,A->x0);
}
void Fp_add(struct Fp *ANS,struct Fp *A,struct Fp *B){
	mpz_add(ANS->x0,A->x0,B->x0);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_add_ui(struct Fp *ANS,struct Fp *A,unsigned long int a){
	mpz_add_ui(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_add_mpz(struct Fp *ANS,struct Fp *A,mpz_t a){
	mpz_add(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_sub(struct Fp *ANS,struct Fp *A,struct Fp *B){
	mpz_sub(ANS->x0,A->x0,B->x0);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_sub_ui(struct Fp *ANS,struct Fp *A,unsigned long int a){
	mpz_sub_ui(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
void Fp_sub_mpz(struct Fp *ANS,struct Fp *A,mpz_t a){
	mpz_sub(ANS->x0,A->x0,a);
	mpz_mod(ANS->x0,ANS->x0,prime);
}
/*------------------------------inverse---------------------------------*/
void Fp_inv(struct Fp *ANS,struct Fp *A){
	/*mpz_t r0,r1,r2,a0,a1,a2,b0,b1,b2,q,t;
	mpz_init(r0);
	mpz_init(r1);
	mpz_init(r2);
	mpz_init(a0);
	mpz_init(a1);
	mpz_init(a2);
	mpz_init(b0);
	mpz_init(b1);
	mpz_init(b2);
	mpz_init(q);
	
	mpz_init(t);
	mpz_set_ui(a0,1);
	mpz_set_ui(b0,0);
	mpz_set(r0,A->x0);
	mpz_set_ui(a1,0);
	mpz_set_ui(b1,1);
	mpz_set(r1,prime);
	while(mpz_cmp_ui(r1,0)>0){
		mpz_mod(r2,r0,r1);
		mpz_tdiv_q(q,r0,r1);
		mpz_mul(t,q,a1);
		mpz_sub(a2,a0,t);
		mpz_mod(a2,a2,prime);
		mpz_mul(t,q,b1);
		mpz_sub(b2,b0,t);
		mpz_sub(b2,b2,prime);
		mpz_set(r0,r1);	mpz_set(r1,r2);
		mpz_set(a0,a1);	mpz_set(a1,a2);
		mpz_set(b0,b1);	mpz_set(b1,b2);
	}
	mpz_set(ANS->x0,a0);
	
	mpz_clear(r0);
	mpz_clear(r1);
	mpz_clear(r2);
	mpz_clear(a0);
	mpz_clear(a1);
	mpz_clear(a2);
	mpz_clear(b0);
	mpz_clear(b1);
	mpz_clear(b2);
	mpz_clear(q);
	mpz_clear(t);*/
	mpz_invert(ANS->x0,A->x0,prime);
}
/*------------------------------legendre-------------------------------*/
int Fp_legendre(struct Fp *A){
	/*int L;
	mpz_t x;
	mpz_init(x);
	mpz_t y;
	mpz_init(y);
	mpz_t t;
	mpz_init(t);
	mpz_t ANS;
	mpz_init(ANS);
	mpz_t buf;
	mpz_init(buf);
	
	mpz_set(x,A->x0);
	mpz_mod(ANS,x,prime);
	if(mpz_cmp_ui(ANS,0)==0){
		return 0;
	}
	mpz_set(y,prime);
	L=1;
	while(1){
		mpz_mod(x,x,y);
		mpz_tdiv_q_ui(buf,y,2);
		mpz_add_ui(buf,buf,1);
		if(mpz_cmp(x,buf)>0){
			mpz_sub(buf,y,x);
			mpz_set(x,buf);
			mpz_mod_ui(ANS,y,4);
			if(mpz_cmp_ui(ANS,3)==0){
				L=-L;
			}
		}
		mpz_mod_ui(ANS,x,4);
		while(mpz_cmp_ui(ANS,0)==0){		
			mpz_tdiv_q_ui(x,x,4);
			mpz_mod_ui(ANS,x,4);
		}
		mpz_mod_ui(ANS,x,2);
		if(mpz_cmp_ui(ANS,0)==0){
			mpz_tdiv_q_ui(x,x,2);
			mpz_mod_ui(ANS,y,8);
			if(mpz_cmp_ui(ANS,3)==0
			|| mpz_cmp_ui(ANS,5)==0) L=-L;
		}
		if(mpz_cmp_ui(x,1)==0) return L;
		mpz_mod_ui(ANS,x,4);
		if(mpz_cmp_ui(ANS,3)==0){		
			mpz_mod_ui(ANS,y,4);
			if(mpz_cmp_ui(ANS,3)==0) L=-L;
		}
		mpz_set(t,y);
		mpz_set(y,x);
		mpz_set(x,t);
	}
	
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(t);
	mpz_clear(ANS);
	mpz_clear(buf);*/
	return mpz_legendre(A->x0,prime);
}
int Fp_isCNR(struct Fp *A){
	struct Fp buf;
	Fp_init(&buf);
	mpz_t exp;
	mpz_init(exp);
	
	mpz_sub_ui(exp,prime,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp_cmp_ui(&buf,1)==0){
		Fp_clear(&buf);
		return 1;
	}else if(Fp_cmp_ui(&buf,0)==0){
		Fp_clear(&buf);
		return 0;
	}else{
		Fp_clear(&buf);
		return -1;
	}
}
/*---------------------------------sqr----------------------------------*/
void Fp_sqrt(struct Fp *ANS,struct Fp *A){
	struct Fp x,y,t,k,n,buf;
	Fp_init(&x);
	Fp_init(&y);
	Fp_init(&t);
	Fp_init(&k);
	Fp_init(&n);
	Fp_init(&buf);
	unsigned long int e,m;
	mpz_t exp,q,z,result;
	mpz_init(exp);
	mpz_init(q);
	mpz_init(z);
	mpz_init(result);
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	Fp_random(&n,state);
	
	while(Fp_legendre(&n)!=-1){
		Fp_random(&n,state);
	}
	mpz_sub_ui(q,prime,1);
	mpz_mod_ui(result,q,2);
	e=0;
	while(mpz_cmp_ui(result,0)==0){
		mpz_tdiv_q_ui(q,q,2);
		mpz_mod_ui(result,q,2);
		e++;
	}
	Fp_pow(&y,&n,q);
	mpz_set_ui(z,e);
	mpz_sub_ui(exp,q,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp_pow(&x,A,exp);
	Fp_mul(&buf,&x,&x);
	Fp_mul(&k,&buf,A);
	Fp_mul(&x,&x,A);
	while(Fp_cmp_one(&k)!=0){
		m=1;
		mpz_ui_pow_ui(exp,2,m);
		Fp_pow(&buf,&k,exp);
		while(Fp_cmp_one(&buf)!=0){
			m++;
			mpz_ui_pow_ui(exp,2,m);
			Fp_pow(&buf,&k,exp);
		}
		mpz_sub_ui(exp,z,m);
		mpz_sub_ui(exp,exp,1);
		mpz_ui_pow_ui(result,2,mpz_get_ui(exp));
		Fp_pow(&t,&y,result);
		Fp_mul(&y,&t,&t);
		mpz_set_ui(z,m);
		Fp_mul(&x,&x,&t);
		Fp_mul(&k,&k,&y);
	}
	Fp_set(ANS,&x);
	
	mpz_clear(exp);
	mpz_clear(q);
	mpz_clear(z);
	mpz_clear(result);
	Fp_clear(&x);
	Fp_clear(&y);
	Fp_clear(&t);
	Fp_clear(&k);
	Fp_clear(&n);
	Fp_clear(&buf);
}
/*---------------------------------pow----------------------------------*/
void Fp_pow(struct Fp *ANS,struct Fp *A,mpz_t a){
	int i,length;
	length=(int)mpz_sizeinbase(a,2);
	char binary[length];
	mpz_get_str(binary,2,a);
	struct Fp buf;
	Fp_init(&buf);
	Fp_set(&buf,A);
	
	for(i=1; binary[i]!='\0'; i++){
		Fp_mul(&buf,&buf,&buf);
		if(binary[i]=='1'){
			Fp_mul(&buf,A,&buf);
		}
	}
	Fp_set(ANS,&buf);
	
	Fp_clear(&buf);
}
/*---------------------------------cmp----------------------------------*/
int Fp_cmp(struct Fp *A,struct Fp *B){
	if(mpz_cmp(A->x0,B->x0)==0){
		return 0;	
	}
	return 1;
}
int Fp_cmp_ui(struct Fp *A,unsigned long int a){
	if(mpz_cmp_ui(A->x0,a)==0){
		return 0;
	}
	return 1;
}
int Fp_cmp_mpz(struct Fp *A,mpz_t a){
	if(mpz_cmp(A->x0,a)==0){
		return 0;
	}
	return 1;
}
int Fp_cmp_zero(struct Fp *A){
	if(mpz_cmp_ui(A->x0,0)==0){
		return 0;
	}
	return 1;
}
int Fp_cmp_one(struct Fp *A){
	if(mpz_cmp_ui(A->x0,1)==0){
		return 0;
	}
	return 1;
}
/*============================================================================*/
/* Fp2                                                                        */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void Fp2_init(struct Fp2 *P){
	Fp_init(&P->x0);
	Fp_init(&P->x1);
}
/*---------------------------------set----------------------------------*/
void Fp2_set(struct Fp2 *P,struct Fp2 *A){
	Fp_set(&P->x0,&A->x0);
	Fp_set(&P->x1,&A->x1);
}
void Fp2_set_ui(struct Fp2 *P,unsigned long int a){
	Fp_set_ui(&P->x0,a);
	Fp_set_ui(&P->x1,a);
}
void Fp2_set_mpz(struct Fp2 *P,mpz_t a){
	Fp_set_mpz(&P->x0,a);
	Fp_set_mpz(&P->x1,a);
}
void Fp2_set_neg(struct Fp2 *P,struct Fp2 *A){
	Fp_set_neg(&P->x0,&A->x0);
	Fp_set_neg(&P->x1,&A->x1);
}
/*---------------------------------random--------------------------------*/
void Fp2_random(struct Fp2 *P,gmp_randstate_t state){
	Fp_random(&P->x0,state);
	Fp_random(&P->x1,state);
}
/*---------------------------------clear---------------------------------*/
void Fp2_clear(struct Fp2 *P){
	Fp_clear(&P->x0);
	Fp_clear(&P->x1);
}
/*---------------------------------print---------------------------------*/
void Fp2_printf(struct Fp2 *P,char *name){
	printf("%s",name);
	printf("(");
	Fp_printf(&P->x0,"");
	printf(",");
	Fp_printf(&P->x1,"");
	printf(")");
}
/*---------------------------vector calculation--------------------------*/
void Fp2_mul(struct Fp2 *ANS,struct Fp2 *A,struct Fp2 *B){
	struct Fp tmp1,tmp2,tmp3,tmp4;
	Fp_init(&tmp1);
	Fp_init(&tmp2);
	Fp_init(&tmp3);
	Fp_init(&tmp4);
	
	//set
	Fp_mul(&tmp1,&A->x0,&B->x0);//a*c	
	Fp_mul(&tmp2,&A->x1,&B->x1);//b*d
	Fp_add(&tmp3,&A->x0,&A->x1);//a+b
	Fp_add(&tmp4,&B->x0,&B->x1);//c+d
	//x0
	Fp_mul_basis(&ANS->x0,&tmp2);//b*d*v
	Fp_add(&ANS->x0,&ANS->x0,&tmp1);//a*c+b*d*v
	//x1
	Fp_mul(&ANS->x1,&tmp3,&tmp4);//(a+b)(c+d)
	Fp_sub(&ANS->x1,&ANS->x1,&tmp1);
	Fp_sub(&ANS->x1,&ANS->x1,&tmp2);
	
	//clear
	Fp_clear(&tmp1);
	Fp_clear(&tmp2);
	Fp_clear(&tmp3);
	Fp_clear(&tmp4);
}
void Fp2_mul_ui(struct Fp2 *ANS,struct Fp2 *A,unsigned long int a){
	Fp_mul_ui(&ANS->x0,&A->x0,a);
	Fp_mul_ui(&ANS->x1,&A->x1,a);
}
void Fp2_mul_mpz(struct Fp2 *ANS,struct Fp2 *A,mpz_t a){
	Fp_mul_mpz(&ANS->x0,&A->x0,a);
	Fp_mul_mpz(&ANS->x1,&A->x1,a);
}
void Fp2_mul_basis(struct Fp2 *ANS,struct Fp2 *A){
	struct Fp tmp;
	Fp_init(&tmp);
	Fp_set(&tmp,&A->x0);
	
	Fp_sub(&ANS->x0,&tmp,&A->x1);
	Fp_add(&ANS->x1,&tmp,&A->x1);
	
	Fp_clear(&tmp);
}
void Fp2_squaring(struct Fp2 *ANS,struct Fp2 *A){
	struct Fp tmp1,tmp2;
	Fp_init(&tmp1);
	Fp_init(&tmp2);
	
	Fp_add(&tmp1,&A->x0,&A->x1);
	Fp_sub(&tmp2,&A->x0,&A->x1);
	//x1
	Fp_mul(&ANS->x1,&A->x0,&A->x1);
	Fp_add(&ANS->x1,&ANS->x1,&ANS->x1);
	//x0
	Fp_mul(&ANS->x0,&tmp1,&tmp2);
	
	Fp_clear(&tmp1);
	Fp_clear(&tmp2);
}
void Fp2_inv_basis(struct Fp2 *ANS,struct Fp2 *A){
	//Fp2_mul(ANS,A,&Fp2_basis_inv);
	struct Fp2 tmp;
	Fp2_init(&tmp);
	Fp2_set(&tmp,A);
	
	Fp_add(&ANS->x0,&tmp.x0,&tmp.x1);
	Fp_mul_mpz(&ANS->x0,&ANS->x0,Fp2_basis_inv.x0.x0);
	Fp_sub(&ANS->x1,&tmp.x1,&tmp.x0);
	Fp_mul_mpz(&ANS->x1,&ANS->x1,Fp2_basis_inv.x0.x0);
	
	Fp2_clear(&tmp);
}
void Fp2_add(struct Fp2 *ANS,struct Fp2 *A,struct Fp2 *B){
	Fp_add(&ANS->x0,&A->x0,&B->x0);
	Fp_add(&ANS->x1,&A->x1,&B->x1);
}
void Fp2_add_ui(struct Fp2 *ANS,struct Fp2 *A,unsigned long int a){
	Fp_add_ui(&ANS->x0,&A->x0,a);
	Fp_add_ui(&ANS->x1,&A->x1,a);
}
void Fp2_add_mpz(struct Fp2 *ANS,struct Fp2 *A,mpz_t a){
	Fp_add_mpz(&ANS->x0,&A->x0,a);
	Fp_add_mpz(&ANS->x1,&A->x1,a);
}
void Fp2_sub(struct Fp2 *ANS,struct Fp2 *A,struct Fp2 *B){
	Fp_sub(&ANS->x0,&A->x0,&B->x0);
	Fp_sub(&ANS->x1,&A->x1,&B->x1);
}
void Fp2_sub_ui(struct Fp2 *ANS,struct Fp2 *A,unsigned long int a){
	Fp_sub_ui(&ANS->x0,&A->x0,a);
	Fp_sub_ui(&ANS->x1,&A->x1,a);
}
void Fp2_sub_mpz(struct Fp2 *ANS,struct Fp2 *A,mpz_t a){
	Fp_sub_mpz(&ANS->x0,&A->x0,a);
	Fp_sub_mpz(&ANS->x1,&A->x1,a);
}
/*------------------------------inverse---------------------------------*/
void Fp2_inv(struct Fp2 *ANS,struct Fp2 *A){
	struct Fp2 frob,buf;
	Fp2_init(&frob);
	Fp2_init(&buf);
	
	Fp2_inv_map(&frob,A);
	Fp2_mul(&buf,A,&frob);
	//Fp_inv(&buf.x0,&buf.x0);
	mpz_invert(buf.x0.x0,buf.x0.x0,prime);
	Fp2_mul_mpz(ANS,&frob,buf.x0.x0);
	
	Fp2_clear(&frob);
	Fp2_clear(&buf);
}
void Fp2_inv_map(struct Fp2 *ANS,struct Fp2 *A){
	Fp_set(&ANS->x0,&A->x0);
	Fp_set_neg(&ANS->x1,&A->x1);
}
/*------------------------------legendre-------------------------------*/
int Fp2_legendre(struct Fp2 *A){
	struct Fp2 buf;
	Fp2_init(&buf);
	mpz_t exp;
	mpz_init(exp);
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp2_cmp_one(&buf)==0){
		Fp2_clear(&buf);
		return 1;
	}else if(Fp2_cmp_zero(&buf)==0){
		Fp2_clear(&buf);
		return 0;
	}else{
		Fp2_clear(&buf);
		return -1;
	}
}
int Fp2_isCNR(struct Fp2 *A){
	struct Fp2 buf;
	Fp2_init(&buf);
	mpz_t exp;
	mpz_init(exp);
	
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp2_cmp_one(&buf)==0){
		Fp2_clear(&buf);
		return 1;
	}else if(Fp2_cmp_zero(&buf)==0){
		Fp2_clear(&buf);
		return 0;
	}else{
		Fp2_clear(&buf);
		return -1;
	}
}
/*---------------------------------sqr----------------------------------*/
void Fp2_sqrt(struct Fp2 *ANS,struct Fp2 *A){
	struct Fp2 x,y,t,k,n,buf;
	Fp2_init(&x);
	Fp2_init(&y);
	Fp2_init(&t);
	Fp2_init(&k);
	Fp2_init(&n);
	Fp2_init(&buf);
	unsigned long int e,m;
	mpz_t exp,q,z,result;
	mpz_init(exp);
	mpz_init(q);
	mpz_init(z);
	mpz_init(result);
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	Fp2_random(&n,state);
	while(Fp2_legendre(&n)!=-1){
		Fp2_random(&n,state);
	}
	mpz_pow_ui(q,prime,2);
	mpz_sub_ui(q,q,1);
	mpz_mod_ui(result,q,2);
	e=0;
	while(mpz_cmp_ui(result,0)==0){
		mpz_tdiv_q_ui(q,q,2);
		mpz_mod_ui(result,q,2);
		e++;
	}
	Fp2_pow(&y,&n,q);
	mpz_set_ui(z,e);
	mpz_sub_ui(exp,q,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&x,A,exp);
	Fp2_mul(&buf,&x,&x);
	Fp2_mul(&k,&buf,A);
	Fp2_mul(&x,&x,A);
	while(Fp2_cmp_one(&k)!=0){
		m=1;
		mpz_ui_pow_ui(exp,2,m);
		Fp2_pow(&buf,&k,exp);
		while(Fp2_cmp_one(&buf)!=0){
			m++;
			mpz_ui_pow_ui(exp,2,m);
			Fp2_pow(&buf,&k,exp);
		}
		mpz_sub_ui(exp,z,m);
		mpz_sub_ui(exp,exp,1);
		mpz_ui_pow_ui(result,2,mpz_get_ui(exp));
		Fp2_pow(&t,&y,result);
		Fp2_mul(&y,&t,&t);
		mpz_set_ui(z,m);
		Fp2_mul(&x,&x,&t);
		Fp2_mul(&k,&k,&y);
	}
	Fp2_set(ANS,&x);
	
	mpz_clear(exp);
	mpz_clear(q);
	mpz_clear(z);
	mpz_clear(result);
	Fp2_clear(&x);
	Fp2_clear(&y);
	Fp2_clear(&t);
	Fp2_clear(&k);
	Fp2_clear(&n);
	Fp2_clear(&buf);
}
/*---------------------------------pow----------------------------------*/
void Fp2_pow(struct Fp2 *ANS,struct Fp2 *A,mpz_t a){
	int i,length;
	length=(int)mpz_sizeinbase(a,2);
	char binary[length];
	mpz_get_str(binary,2,a);
	struct Fp2 buf;
	Fp2_init(&buf);
	Fp2_set(&buf,A);
	
	for(i=1; binary[i]!='\0'; i++){
		//Fp2_mul(&buf,&buf,&buf);
		Fp2_squaring(&buf,&buf);
		if(binary[i]=='1'){
			Fp2_mul(&buf,A,&buf);
		}
	}
	
	Fp2_set(ANS,&buf);
	Fp2_clear(&buf);
}
/*---------------------------------cmp----------------------------------*/
int Fp2_cmp(struct Fp2 *A,struct Fp2 *B){
	if(Fp_cmp(&A->x0,&B->x0)==0 && Fp_cmp(&A->x1,&B->x1)==0){
		return 0;	
	}
	return 1;
}
int Fp2_cmp_ui(struct Fp2 *A,unsigned long int a){
	if(Fp_cmp_ui(&A->x0,a)==0 && Fp_cmp_ui(&A->x1,a)==0){
		return 0;
	}
	return 1;
}
int Fp2_cmp_mpz(struct Fp2 *A,mpz_t a){
	if(Fp_cmp_mpz(&A->x0,a)==0 && Fp_cmp_mpz(&A->x1,a)==0){
		return 0;
	}
	return 1;
}
int Fp2_cmp_zero(struct Fp2 *A){
	if(Fp_cmp_zero(&A->x0)==0 && Fp_cmp_zero(&A->x1)==0){
		return 0;
	}
	return 1;
}
int Fp2_cmp_one(struct Fp2 *A){
	if(Fp_cmp_one(&A->x0)==0 && Fp_cmp_zero(&A->x1)==0){
		return 0;
	}
	return 1;
}
void Fp2_frobenius_1(struct Fp2 *ANS,struct Fp2 *A){
	Fp_set(&ANS->x0,&A->x0);
	Fp_set_neg(&ANS->x1,&A->x1);
}
void Fp2_frobenius_2(struct Fp2 *ANS,struct Fp2 *A){
	Fp2_set(ANS,A);
}
void Fp2_frobenius_3(struct Fp2 *ANS,struct Fp2 *A){
	Fp_set(&ANS->x0,&A->x0);
	Fp_set_neg(&ANS->x1,&A->x1);
}
void Fp2_frobenius_10(struct Fp2 *ANS,struct Fp2 *A){
	Fp2_set(ANS,A);
}
/*============================================================================*/
/* Fp4                                                                        */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void Fp4_init(struct Fp4 *P){
	Fp2_init(&P->x0);
	Fp2_init(&P->x1);
}
/*---------------------------------set----------------------------------*/
void Fp4_set(struct Fp4 *P,struct Fp4 *A){
	Fp2_set(&P->x0,&A->x0);
	Fp2_set(&P->x1,&A->x1);
}
void Fp4_set_ui(struct Fp4 *P,unsigned long int a){
	Fp2_set_ui(&P->x0,a);
	Fp2_set_ui(&P->x1,a);
}
void Fp4_set_mpz(struct Fp4 *P,mpz_t a){
	Fp2_set_mpz(&P->x0,a);
	Fp2_set_mpz(&P->x1,a);	
}
void Fp4_set_neg(struct Fp4 *P,struct Fp4 *A){
	Fp2_set_neg(&P->x0,&A->x0);
	Fp2_set_neg(&P->x1,&A->x1);
}
/*---------------------------------random--------------------------------*/
void Fp4_random(struct Fp4 *P,gmp_randstate_t state){
	Fp2_random(&P->x0,state);
	Fp2_random(&P->x1,state);
}
/*---------------------------------clear---------------------------------*/
void Fp4_clear(struct Fp4 *P){
	Fp2_clear(&P->x0);
	Fp2_clear(&P->x1);
}
/*---------------------------------print---------------------------------*/
void Fp4_printf(struct Fp4 *P,char *name){
	printf("%s",name);
	printf("(");
	Fp2_printf(&P->x0,"");
	printf(",");
	Fp2_printf(&P->x1,"");
	printf(")");
}
/*---------------------------vector calculation--------------------------*/
void Fp4_mul(struct Fp4 *ANS,struct Fp4 *A,struct Fp4 *B){
	struct Fp2 tmp1,tmp2;
	Fp2_init(&tmp1);
	Fp2_init(&tmp2);
	
	//set
	Fp2_mul(&tmp2,&A->x1,&B->x1);//b*d
	Fp2_add(&tmp1,&A->x0,&A->x1);//a+b
	Fp2_add(&ANS->x1,&B->x0,&B->x1);//c+d
	Fp2_mul(&ANS->x1,&tmp1,&ANS->x1);//(a+b)(c+d)
	Fp2_mul(&tmp1,&A->x0,&B->x0);//a*c
	//x0
	Fp2_mul_basis(&ANS->x0,&tmp2);//b*d*v
	Fp2_add(&ANS->x0,&ANS->x0,&tmp1);//a*c+b*d*v
	//x1
	Fp2_sub(&ANS->x1,&ANS->x1,&tmp1);
	Fp2_sub(&ANS->x1,&ANS->x1,&tmp2);
	
	//clear
	Fp2_clear(&tmp1);
	Fp2_clear(&tmp2);
}
void Fp4_mul_ui(struct Fp4 *ANS,struct Fp4 *A,unsigned long int a){
	Fp2_mul_ui(&ANS->x0,&A->x0,a);
	Fp2_mul_ui(&ANS->x1,&A->x1,a);
}
void Fp4_mul_mpz(struct Fp4 *ANS,struct Fp4 *A,mpz_t a){
	Fp2_mul_mpz(&ANS->x0,&A->x0,a);
	Fp2_mul_mpz(&ANS->x1,&A->x1,a);
}
void Fp4_mul_basis(struct Fp4 *ANS,struct Fp4 *A){
	struct Fp4 tmp;
	Fp4_init(&tmp);
	Fp4_set(&tmp,A);
	
	Fp_sub(&ANS->x0.x0,&tmp.x1.x0,&tmp.x1.x1);
	Fp_add(&ANS->x0.x1,&tmp.x1.x0,&tmp.x1.x1);
	Fp_set(&ANS->x1.x0,&tmp.x0.x0);
	Fp_set(&ANS->x1.x1,&tmp.x0.x1);
	
	Fp4_clear(&tmp);
}
void Fp4_squaring(struct Fp4 *ANS,struct Fp4 *A){
	struct Fp2 tmp1,tmp2,tmp3;
	Fp2_init(&tmp1);
	Fp2_init(&tmp2);
	Fp2_init(&tmp3);
	
	Fp2_add(&tmp1,&A->x0,&A->x1);
	Fp2_mul_basis(&tmp2,&A->x1);
	Fp2_add(&tmp2,&tmp2,&A->x0);
	Fp2_mul(&tmp3,&A->x0,&A->x1);
	
	//x0
	Fp2_mul(&ANS->x0,&tmp1,&tmp2);
	Fp2_sub(&ANS->x0,&ANS->x0,&tmp3);
	Fp2_mul_basis(&tmp1,&tmp3);
	Fp2_sub(&ANS->x0,&ANS->x0,&tmp1);
	//x1
	Fp2_add(&ANS->x1,&tmp3,&tmp3);
	
	Fp2_clear(&tmp1);
	Fp2_clear(&tmp2);
	Fp2_clear(&tmp3);
}
void Fp4_add(struct Fp4 *ANS,struct Fp4 *A,struct Fp4 *B){
	Fp2_add(&ANS->x0,&A->x0,&B->x0);
	Fp2_add(&ANS->x1,&A->x1,&B->x1);
}
void Fp4_add_ui(struct Fp4 *ANS,struct Fp4 *A,unsigned long int a){
	Fp2_add_ui(&ANS->x0,&A->x0,a);
	Fp2_add_ui(&ANS->x1,&A->x1,a);
}
void Fp4_add_mpz(struct Fp4 *ANS,struct Fp4 *A,mpz_t a){
	Fp2_add_mpz(&ANS->x0,&ANS->x0,a);
	Fp2_add_mpz(&ANS->x1,&ANS->x1,a);
}
void Fp4_sub(struct Fp4 *ANS,struct Fp4 *A,struct Fp4 *B){
	Fp2_sub(&ANS->x0,&A->x0,&B->x0);
	Fp2_sub(&ANS->x1,&A->x1,&B->x1);
}
void Fp4_sub_ui(struct Fp4 *ANS,struct Fp4 *A,unsigned long int a){
	Fp2_sub_ui(&ANS->x0,&ANS->x0,a);
	Fp2_sub_ui(&ANS->x1,&ANS->x1,a);
}
void Fp4_sub_mpz(struct Fp4 *ANS,struct Fp4 *A,mpz_t a){
	Fp2_sub_mpz(&ANS->x0,&ANS->x0,a);
	Fp2_sub_mpz(&ANS->x1,&ANS->x1,a);
}
/*-------------------------------inverse--------------------------------*/
void Fp4_inv(struct Fp4 *ANS,struct Fp4 *A){
	struct Fp4 frob,buf;
	Fp4_init(&frob);
	Fp4_init(&buf);
	
	Fp4_inv_map(&frob,A);
	Fp4_mul(&buf,A,&frob);
	Fp2_inv(&buf.x0,&buf.x0);
	Fp2_mul(&ANS->x0,&frob.x0,&buf.x0);
	Fp2_mul(&ANS->x1,&frob.x1,&buf.x0);
	
	Fp4_clear(&frob);
	Fp4_clear(&buf);
}
void Fp4_inv_map(struct Fp4 *ANS,struct Fp4 *A){	
	Fp2_set(&ANS->x0,&A->x0);
	Fp2_set_neg(&ANS->x1,&A->x1);
}
/*-------------------------------legendre-------------------------------*/
int Fp4_legendre(struct Fp4 *A){
	mpz_t exp;		mpz_init(exp);
	struct Fp4 buf;
	Fp4_init(&buf);
	
	mpz_pow_ui(exp,prime,4);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp4_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp4_cmp_one(&buf)==0){
		Fp4_clear(&buf);
		return 1;
	}else if(Fp4_cmp_zero(&buf)==0){
		Fp4_clear(&buf);
		return 0;
	}else{
		Fp4_clear(&buf);
		return -1;
	}
}
int Fp4_isCNR(struct Fp4 *A){
	struct Fp4 buf;
	Fp4_init(&buf);
	mpz_t exp;
	mpz_init(exp);
	
	mpz_pow_ui(exp,prime,4);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp4_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp4_cmp_one(&buf)==0){
		Fp4_clear(&buf);
		return 1;
	}else if(Fp4_cmp_zero(&buf)==0){
		Fp4_clear(&buf);
		return 0;
	}else{
		Fp4_clear(&buf);
		return -1;
	}
}
/*---------------------------------sqr----------------------------------*/
void Fp4_sqrt(struct Fp4 *ANS,struct Fp4 *A){
	struct Fp4 x,y,t,k,n,buf;
	Fp4_init(&x);
	Fp4_init(&y);
	Fp4_init(&t);
	Fp4_init(&k);
	Fp4_init(&n);
	Fp4_init(&buf);
	unsigned long int e,m;
	mpz_t exp,q,z,result;
	mpz_init(exp);
	mpz_init(q);
	mpz_init(z);
	mpz_init(result);
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	Fp4_random(&n,state);
	while(Fp4_legendre(&n)!=-1){
		Fp4_random(&n,state);
	}
	mpz_pow_ui(q,prime,4);
	mpz_sub_ui(q,q,1);
	mpz_mod_ui(result,q,2);
	e=0;
	while(mpz_cmp_ui(result,0)==0){
		mpz_tdiv_q_ui(q,q,2);
		mpz_mod_ui(result,q,2);
		e++;
	}
	Fp4_pow(&y,&n,q);
	mpz_set_ui(z,e);	
	mpz_sub_ui(exp,q,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp4_pow(&x,A,exp);
	Fp4_mul(&buf,&x,&x);
	Fp4_mul(&k,&buf,A);
	Fp4_mul(&x,&x,A);
	while(Fp4_cmp_one(&k)!=0){
		m=1;
		mpz_ui_pow_ui(exp,2,m);
		Fp4_pow(&buf,&k,exp);
		while(Fp4_cmp_one(&buf)!=0){
			m++;
			mpz_ui_pow_ui(exp,2,m);
			Fp4_pow(&buf,&k,exp);
		}
		mpz_sub_ui(exp,z,m);
		mpz_sub_ui(exp,exp,1);
		mpz_ui_pow_ui(result,2,mpz_get_ui(exp));
		Fp4_pow(&t,&y,result);
		Fp4_mul(&y,&t,&t);
		mpz_set_ui(z,m);
		Fp4_mul(&x,&x,&t);	
		Fp4_mul(&k,&k,&y);
	}
	Fp4_set(ANS,&x);
	
	mpz_clear(q);
	mpz_clear(z);
	mpz_clear(exp);
	mpz_clear(result);
	Fp4_clear(&x);
	Fp4_clear(&y);
	Fp4_clear(&t);
	Fp4_clear(&k);
	Fp4_clear(&n);
	Fp4_clear(&buf);
}
/*---------------------------------pow----------------------------------*/
void Fp4_pow(struct Fp4 *ANS,struct Fp4 *A,mpz_t a){
	int i,length;
	length=(int)mpz_sizeinbase(a,2);
	char binary[length];
	mpz_get_str(binary,2,a);
	struct Fp4 buf;
	Fp4_init(&buf);
	Fp4_set(&buf,A);
	
	for(i=1; binary[i]!='\0'; i++){
		//Fp4_mul(&buf,&buf,&buf);
		Fp4_squaring(&buf,&buf);
		if(binary[i]=='1'){
			Fp4_mul(&buf,A,&buf);
		}
	}
	
	Fp4_set(ANS,&buf);
	Fp4_clear(&buf);
}
/*---------------------------------cmp----------------------------------*/
int Fp4_cmp(struct Fp4 *A,struct Fp4 *B){
	if(Fp2_cmp(&A->x0,&B->x0)==0 && Fp2_cmp(&A->x1,&B->x1)==0){
		return 0;	
	}
	return 1;
}
int Fp4_cmp_ui(struct Fp4 *A,unsigned long int a){
	if(Fp2_cmp_ui(&A->x0,a)==0 && Fp2_cmp_ui(&A->x1,a)==0){
		return 0;
	}
	return 1;
}
int Fp4_cmp_mpz(struct Fp4 *A,mpz_t a){
	if(Fp2_cmp_mpz(&A->x0,a)==0 && Fp2_cmp_mpz(&A->x1,a)==0){
		return 0;
	}
	return 1;
}
int Fp4_cmp_zero(struct Fp4 *A){
	if(Fp2_cmp_zero(&A->x0)==0 && Fp2_cmp_zero(&A->x1)==0){
		return 0;
	}
	return 1;
}
int Fp4_cmp_one(struct Fp4 *A){
	if(Fp2_cmp_one(&A->x0)==0 && Fp2_cmp_zero(&A->x1)==0){
		return 0;
	}
	return 1;
}
/*============================================================================*/
/* Fp12                                                                       */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void Fp12_init(struct Fp12 *P){
	Fp4_init(&P->x0);
	Fp4_init(&P->x1);
	Fp4_init(&P->x2);
} 
/*---------------------------------set----------------------------------*/
void Fp12_set(struct Fp12 *P,struct Fp12 *A){
	Fp4_set(&P->x0,&A->x0);
	Fp4_set(&P->x1,&A->x1);
	Fp4_set(&P->x2,&A->x2);
}
void Fp12_set_ui(struct Fp12 *P,unsigned long int a){
	Fp4_set_ui(&P->x0,a);
	Fp4_set_ui(&P->x1,a);
	Fp4_set_ui(&P->x2,a);
}
void Fp12_set_mpz(struct Fp12 *P,mpz_t a){
	Fp4_set_mpz(&P->x0,a);
	Fp4_set_mpz(&P->x1,a);
	Fp4_set_mpz(&P->x2,a);
}
void Fp12_set_neg(struct Fp12 *P,struct Fp12 *A){
	Fp4_set_neg(&P->x0,&A->x0);
	Fp4_set_neg(&P->x1,&A->x1);
	Fp4_set_neg(&P->x2,&A->x2);
}
/*---------------------------------random--------------------------------*/
void Fp12_random(struct Fp12 *P,gmp_randstate_t state){
	Fp4_random(&P->x0,state);
	Fp4_random(&P->x1,state);
	Fp4_random(&P->x2,state);
}
/*---------------------------------clear---------------------------------*/
void Fp12_clear(struct Fp12 *P){
	Fp4_clear(&P->x0);
	Fp4_clear(&P->x1);
	Fp4_clear(&P->x2);
}
/*---------------------------------print---------------------------------*/
void Fp12_printf(struct Fp12 *P,char *name){
	printf("%s",name);
	printf("(");
	Fp4_printf(&P->x0,"");
	printf(",");
	Fp4_printf(&P->x1,"");
	printf(",");
	Fp4_printf(&P->x2,"");
	printf(")");
}
/*---------------------------vector calculation--------------------------*/
void Fp12_mul(struct Fp12 *ANS,struct Fp12 *A,struct Fp12 *B){
	struct Fp4 tmp00,tmp11,tmp22,buf,t0,t1,t2;
	Fp4_init(&tmp00);
	Fp4_init(&tmp11);
	Fp4_init(&tmp22);
	Fp4_init(&buf);
	Fp4_init(&t0);
	Fp4_init(&t1);
	Fp4_init(&t2);
	
	//set
	Fp4_mul(&tmp00,&A->x0,&B->x0);//x0*y0
	Fp4_mul(&tmp11,&A->x1,&B->x1);//x1*y1
	Fp4_mul(&tmp22,&A->x2,&B->x2);//x2*y2
	
	Fp4_add(&t0,&A->x0,&A->x1);//x0+x1
	Fp4_add(&buf,&B->x0,&B->x1);//y0+y1
	Fp4_mul(&t0,&t0,&buf);//(x0+x1)(y0+y1)
	
	Fp4_add(&t1,&A->x1,&A->x2);//x1+x2
	Fp4_add(&buf,&B->x1,&B->x2);//y1+y2
	Fp4_mul(&t1,&t1,&buf);//(x1+x2)(y1+y2)
	
	Fp4_add(&t2,&B->x0,&B->x2);//y2+y0
	Fp4_add(&buf,&A->x0,&A->x2);//x2+x0
	Fp4_mul(&t2,&t2,&buf);//(x2+x0)(y2+y0)
	//x0
	Fp4_sub(&t1,&t1,&tmp11);
	Fp4_sub(&t1,&t1,&tmp22);//(x1+x2)(y1+y2)-x1y1-x2y2
	Fp4_mul_basis(&buf,&t1);
	Fp4_add(&ANS->x0,&tmp00,&buf);
	//x1
	Fp4_sub(&t0,&t0,&tmp00);
	Fp4_sub(&t0,&t0,&tmp11);
	Fp4_mul_basis(&buf,&tmp22);
	Fp4_add(&ANS->x1,&buf,&t0);
	//x2
	Fp4_sub(&t2,&t2,&tmp00);
	Fp4_sub(&t2,&t2,&tmp22);
	Fp4_add(&ANS->x2,&tmp11,&t2);
	
	//clear
	Fp4_clear(&tmp00);
	Fp4_clear(&tmp11);
	Fp4_clear(&tmp22);
	Fp4_clear(&buf);
	Fp4_clear(&t0);
	Fp4_clear(&t1);
	Fp4_clear(&t2);
}
void Fp12_mul_ui(struct Fp12 *ANS,struct Fp12 *A,unsigned long int a){
	Fp4_mul_ui(&ANS->x0,&A->x0,a);
	Fp4_mul_ui(&ANS->x1,&A->x1,a);
	Fp4_mul_ui(&ANS->x2,&A->x2,a);
}
void Fp12_mul_mpz(struct Fp12 *ANS,struct Fp12 *A,mpz_t a){
	Fp4_mul_mpz(&ANS->x0,&A->x0,a);
	Fp4_mul_mpz(&ANS->x1,&A->x1,a);
	Fp4_mul_mpz(&ANS->x2,&A->x2,a);
}
void Fp12_squaring(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp4 tmp00,tmp12_2,tmp01_2,tmp22,buf;
	Fp4_init(&tmp00);
	Fp4_init(&tmp22);
	Fp4_init(&tmp12_2);
	Fp4_init(&tmp01_2);
	Fp4_init(&buf);
	
	Fp4_squaring(&tmp00,&A->x0);		//x0^2
	Fp4_squaring(&tmp22,&A->x2);		//x2^2
	Fp4_add(&buf,&A->x1,&A->x1);		//2x1
	Fp4_mul(&tmp12_2,&buf,&A->x2);	//2x1x2
	Fp4_mul(&tmp01_2,&A->x0,&buf);	//2x0x1
	Fp4_add(&buf,&A->x0,&A->x1);		//x0+x1+x2
	Fp4_add(&buf,&buf,&A->x2);
	
	//x0
	Fp4_mul_basis(&ANS->x0,&tmp12_2);
	Fp4_add(&ANS->x0,&ANS->x0,&tmp00);
	//x1
	Fp4_mul_basis(&ANS->x1,&tmp22);
	Fp4_add(&ANS->x1,&ANS->x1,&tmp01_2);
	//x2
	Fp4_squaring(&ANS->x2,&buf);
	Fp4_add(&buf,&tmp00,&tmp22);
	Fp4_add(&buf,&buf,&tmp12_2);
	Fp4_add(&buf,&buf,&tmp01_2);
	Fp4_sub(&ANS->x2,&ANS->x2,&buf);
	
	Fp4_clear(&tmp00);
	Fp4_clear(&tmp22);
	Fp4_clear(&tmp12_2);
	Fp4_clear(&tmp01_2);
	Fp4_clear(&buf);
}
void Fp12_add(struct Fp12 *ANS,struct Fp12 *A,struct Fp12 *B){
	Fp4_add(&ANS->x0,&A->x0,&B->x0);
	Fp4_add(&ANS->x1,&A->x1,&B->x1);
	Fp4_add(&ANS->x2,&A->x2,&B->x2);
}
void Fp12_add_ui(struct Fp12 *ANS,struct Fp12 *A,unsigned long int a){
	Fp4_add_ui(&ANS->x0,&A->x0,a);
	Fp4_add_ui(&ANS->x1,&A->x1,a);
	Fp4_add_ui(&ANS->x2,&A->x2,a);
}
void Fp12_add_mpz(struct Fp12 *ANS,struct Fp12 *A,mpz_t a){
	Fp4_add_mpz(&ANS->x0,&A->x0,a);
	Fp4_add_mpz(&ANS->x1,&A->x1,a);
	Fp4_add_mpz(&ANS->x2,&A->x2,a);
}
void Fp12_sub(struct Fp12 *ANS,struct Fp12 *A,struct Fp12 *B){
	Fp4_sub(&ANS->x0,&A->x0,&B->x0);
	Fp4_sub(&ANS->x1,&A->x1,&B->x1);
	Fp4_sub(&ANS->x2,&A->x2,&B->x2);
}
void Fp12_sub_ui(struct Fp12 *ANS,struct Fp12 *A,unsigned long int a){
	Fp4_sub_ui(&ANS->x0,&A->x0,a);
	Fp4_sub_ui(&ANS->x1,&A->x1,a);
	Fp4_sub_ui(&ANS->x2,&A->x2,a);
}
void Fp12_sub_mpz(struct Fp12 *ANS,struct Fp12 *A,mpz_t a){
	Fp4_sub_mpz(&ANS->x0,&A->x0,a);
	Fp4_sub_mpz(&ANS->x1,&A->x1,a);
	Fp4_sub_mpz(&ANS->x2,&A->x2,a);
}
/*------------------------------inverse---------------------------------*/
void Fp12_inv(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp12 frob1,frob2,buf1, buf2;
	Fp12_init(&frob1);
	Fp12_init(&frob2);
	Fp12_init(&buf1);
	Fp12_init(&buf2);
	
	Fp12_inv_map1(&frob1,A);
	Fp12_inv_map2(&frob2,A);
	Fp12_mul(&buf1,&frob1,&frob2);
	Fp12_mul(&buf2,&buf1,A);
	Fp4_inv(&buf2.x0,&buf2.x0);
	Fp4_mul(&ANS->x0,&buf1.x0,&buf2.x0);
	Fp4_mul(&ANS->x1,&buf1.x1,&buf2.x0);
	Fp4_mul(&ANS->x2,&buf1.x2,&buf2.x0);
	
	Fp12_clear(&frob1);
	Fp12_clear(&frob2);
	Fp12_clear(&buf1);
	Fp12_clear(&buf2);
}
void Fp12_inv_map1(struct Fp12 *ANS,struct Fp12 *A){
	Fp4_set(&ANS->x0,&A->x0);
	Fp4_mul_mpz(&ANS->x1,&A->x1,inv_CNR1.x0);
	Fp4_mul_mpz(&ANS->x2,&A->x2,inv_CNR2.x0);
}
void Fp12_inv_map2(struct Fp12 *ANS,struct Fp12 *A){
	Fp4_set(&ANS->x0,&A->x0);
	Fp4_mul_mpz(&ANS->x1,&A->x1,inv_CNR2.x0);
	Fp4_mul_mpz(&ANS->x2,&A->x2,inv_CNR1.x0);
}
/*-------------------------------legendre-------------------------------*/
int Fp12_legendre(struct Fp12 *A){
	mpz_t exp;		mpz_init(exp);
	struct Fp12 buf;
	Fp12_init(&buf);
	
	mpz_pow_ui(exp,prime,12);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp12_pow(&buf,A,exp);
	
	mpz_clear(exp);
	if(Fp12_cmp_one(&buf)==0){
		Fp12_clear(&buf);
		return 1;
	}else if(Fp12_cmp_zero(&buf)==0){
		Fp12_clear(&buf);
		return 0;
	}else{
		Fp12_clear(&buf);
		return -1;
	}
}
/*---------------------------------sqr----------------------------------*/
void Fp12_sqrt(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp12 buf1,buf2;
	Fp12_init(&buf1);
	Fp12_init(&buf2);
	mpz_t exp,buf;
	mpz_init(exp);
	mpz_init(buf);
	
	Fp12_frobenius_8(&buf1,A);
	Fp12_frobenius_4(&buf2,A);
	Fp12_mul(&buf1,&buf1,&buf2);
	Fp12_mul(&buf1,&buf1,A);
	Fp12_set_ui(&buf2,0);
	Fp4_sqrt(&buf2.x0,&buf1.x0);
	Fp4_inv(&buf2.x0,&buf2.x0);
	Fp4_set(&buf2.x0,&buf2.x0);
	mpz_pow_ui(exp,prime,8);
	mpz_pow_ui(buf,prime,4);
	mpz_add(exp,exp,buf);
	mpz_add_ui(exp,exp,2);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp12_pow(&buf1,A,exp);
	Fp12_mul(&buf1,&buf1,&buf2);
	Fp12_set(ANS,&buf1);
	
	mpz_clear(exp);
	mpz_clear(buf);
	Fp12_clear(&buf1);
	Fp12_clear(&buf2);
}
/*---------------------------------pow----------------------------------*/
void Fp12_pow(struct Fp12 *ANS,struct Fp12 *A,mpz_t a){
	int i,length;
	length=(int)mpz_sizeinbase(a,2);
	char binary[length];
	mpz_get_str(binary,2,a);
	struct Fp12 buf;
	Fp12_init(&buf);
	Fp12_set(&buf,A);
	
	for(i=1; binary[i]!='\0'; i++){
		//Fp12_mul(&buf,&buf,&buf);
		Fp12_squaring(&buf,&buf);
		if(binary[i]=='1'){
			Fp12_mul(&buf,A,&buf);
		}
	}
	
	Fp12_set(ANS,&buf);
	Fp12_clear(&buf);
}
void Fp12_G3_pow(struct Fp12 *ANS,struct Fp12 *A,mpz_t S){
	int i,length_s[4],loop_length;
	struct Fp12 Test;
	Fp12_init(&Test);
	struct Fp12 f,next_f,f_6x,f_6xx,f_36xxx,frobenius_f,frobenius_f_inv,frobenius_f_f,frobenius_f_inv_f,buf_f;
	Fp12_init(&f);
	Fp12_init(&next_f);
	Fp12_init(&f_6x);
	Fp12_init(&f_6xx);
	Fp12_init(&f_36xxx);
	Fp12_init(&frobenius_f);
	Fp12_init(&frobenius_f_inv);
	Fp12_init(&frobenius_f_f);
	Fp12_init(&frobenius_f_inv_f);
	Fp12_init(&buf_f);
	mpz_t a,b,s[4],buf;
	mpz_init(a);
	mpz_init(b);
	for(i=0; i<4; i++){
		mpz_init(s[i]);
	}
	mpz_init(buf);
	//table
	struct Fp12 table[15];
	for(i=0; i<15; i++){
		Fp12_init(&table[i]);
	}
	
	//f
	Fp12_set(&f,A);
	//f_6xx
	Fp12_frobenius_1(&frobenius_f,&f);
	Fp12_set(&f_6xx,&frobenius_f);
	Fp12_inv(&frobenius_f_inv,&frobenius_f);
	//f_6x
	Fp12_mul(&frobenius_f_f,&frobenius_f,&f);
	Fp12_mul(&frobenius_f_inv_f,&frobenius_f_inv,&f);
	Fp12_frobenius_3(&buf_f,&frobenius_f_inv_f);
	Fp12_mul(&f_6x,&frobenius_f_f,&buf_f);
	Fp12_inv(&f_6x,&f_6x);
	//f_36xxx
	Fp12_frobenius_1(&f_36xxx,&f_6x);
	
	//set table
	Fp12_set(&table[0],&f);
	Fp12_set(&table[1],&f_6x);
	Fp12_mul(&table[2],&f_6x,&f);
	Fp12_set(&table[3],&f_6xx);
	Fp12_mul(&table[4],&f_6xx,&f);
	Fp12_mul(&table[5],&f_6xx,&f_6x);
	Fp12_mul(&table[6],&table[5],&f);
	Fp12_set(&table[7],&f_36xxx);
	Fp12_mul(&table[8],&f_36xxx,&f);
	Fp12_mul(&table[9],&f_36xxx,&f_6x);
	Fp12_mul(&table[10],&f_36xxx,&table[2]);
	Fp12_mul(&table[11],&f_36xxx,&f_6xx);
	Fp12_mul(&table[12],&table[11],&f);
	Fp12_mul(&table[13],&table[11],&f_6x);
	Fp12_mul(&table[14],&table[13],&f);
	
	//s0,s1,s2,s3
	mpz_sub_ui(buf,trace_t,1);
	mpz_tdiv_qr(b,a,S,buf);
	mpz_mul_ui(buf,mother_parameter,6);
	mpz_tdiv_qr(s[1],s[0],a,buf);
	mpz_tdiv_qr(s[3],s[2],b,buf);
	
	//binary
	loop_length=0;
	for(i=0; i<4; i++){
		length_s[i]=(int)mpz_sizeinbase(s[i],2);
		//printf("G2 length_s%d:%d\n",i,length_s[i]);
		if(loop_length<length_s[i]){
			loop_length=length_s[i];
		}
	}
	//printf("\n");
	
	//set binary
	char binary_s[4][loop_length+1];
	char check_start[4],*e;
	int start;
	for(i=0; i<4; i++){
		if(length_s[i]==loop_length){
			mpz_get_str(binary_s[i],2,s[i]);
			check_start[3-i]='1';
		}else{
			char binary_buf[loop_length+1];
			mpz_get_str(binary_buf,2,s[i]);
			memset(binary_s[i],'0',sizeof(binary_s[i]));
			memmove(binary_s[i]+loop_length-length_s[i],binary_buf,sizeof(binary_buf));
			check_start[3-i]='0';
		}
		//printf("binary_s%d:%s\n",i,binary_s[i]);
	}
	//printf("\n");
	start=strtol(check_start,&e,2);
	Fp12_set(&next_f,&table[start-1]);
	
	//SCM
	for(i=1; i<loop_length; i++){
		Fp12_squaring(&next_f,&next_f);
		if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[0]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[1]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[2]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[3]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[4]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[5]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[6]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[7]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[8]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[9]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[10]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[11]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[12]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			Fp12_mul(&next_f,&next_f,&table[13]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			Fp12_mul(&next_f,&next_f,&table[14]);
		}
	}
	Fp12_set(ANS,&next_f);
	
	
	Fp12_clear(&Test);
	Fp12_clear(&f);
	Fp12_clear(&next_f);
	Fp12_clear(&f_6x);
	Fp12_clear(&f_6xx);
	Fp12_clear(&f_36xxx);
	Fp12_clear(&frobenius_f);
	Fp12_clear(&frobenius_f_inv);
	Fp12_clear(&frobenius_f_f);
	Fp12_clear(&frobenius_f_inv_f);
	Fp12_clear(&buf_f);
	mpz_clear(a);
	mpz_clear(b);
	for(i=0; i<4; i++){
		mpz_clear(s[i]);
	}
	for(i=0; i<15; i++){
		Fp12_clear(&table[i]);
	}
	mpz_clear(buf);
}
/*-------------------------------frobenius--------------------------------*/
void Fp12_frobenius_1(struct Fp12 *ANS,struct Fp12 *A){
	//x0
	Fp_set(&ANS->x0.x0.x0,&A->x0.x0.x0);
	Fp_set_neg(&ANS->x0.x0.x1,&A->x0.x0.x1);
	Fp_set(&ANS->x0.x1.x0,&A->x0.x1.x0);
	Fp_set_neg(&ANS->x0.x1.x1,&A->x0.x1.x1);
	Fp2_mul(&ANS->x0.x1,&ANS->x0.x1,&scalar1_of_prime_exp_1);
	//x1
	Fp_set(&ANS->x1.x0.x0,&A->x1.x0.x0);
	Fp_set_neg(&ANS->x1.x0.x1,&A->x1.x0.x1);
	Fp2_mul(&ANS->x1.x0,&ANS->x1.x0,&scalar2_of_prime_exp_1);
	Fp_set(&ANS->x1.x1.x0,&A->x1.x1.x0);
	Fp_set_neg(&ANS->x1.x1.x1,&A->x1.x1.x1);
	Fp2_mul(&ANS->x1.x1,&ANS->x1.x1,&scalar1_of_prime_exp_1);
	Fp2_mul(&ANS->x1.x1,&ANS->x1.x1,&scalar2_of_prime_exp_1);
	//x2
	Fp_set(&ANS->x2.x0.x0,&A->x2.x0.x0);
	Fp_set_neg(&ANS->x2.x0.x1,&A->x2.x0.x1);
	Fp2_mul(&ANS->x2.x0,&ANS->x2.x0,&scalar3_of_prime_exp_1);
	Fp_set(&ANS->x2.x1.x0,&A->x2.x1.x0);
	Fp_set_neg(&ANS->x2.x1.x1,&A->x2.x1.x1);
	Fp2_mul(&ANS->x2.x1,&ANS->x2.x1,&scalar1_of_prime_exp_1);
	Fp2_mul(&ANS->x2.x1,&ANS->x2.x1,&scalar3_of_prime_exp_1);
}
void Fp12_frobenius_2(struct Fp12 *ANS,struct Fp12 *A){
	Fp2_set(&ANS->x0.x0,&A->x0.x0);
	Fp2_set_neg(&ANS->x0.x1,&A->x0.x1);
	Fp2_mul_mpz(&ANS->x1.x0,&A->x1.x0,scalar1_of_prime_exp_2.x0.x0);
	Fp2_mul_mpz(&ANS->x1.x1,&A->x1.x1,scalar1_of_prime_exp_2.x0.x0);
	Fp2_set_neg(&ANS->x1.x1,&ANS->x1.x1);
	Fp2_mul_mpz(&ANS->x2.x0,&A->x2.x0,scalar2_of_prime_exp_2.x0.x0);
	Fp2_mul_mpz(&ANS->x2.x1,&A->x2.x1,scalar2_of_prime_exp_2.x0.x0);
	Fp2_set_neg(&ANS->x2.x1,&ANS->x2.x1);
}
void Fp12_frobenius_3(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp tmp;
	Fp_init(&tmp);
	//x0
	Fp_set(&ANS->x0.x0.x0,&A->x0.x0.x0);
	Fp_set_neg(&ANS->x0.x0.x1,&A->x0.x0.x1);
	Fp_set(&ANS->x0.x1.x0,&A->x0.x1.x0);
	Fp_set_neg(&ANS->x0.x1.x1,&A->x0.x1.x1);
	Fp2_mul(&ANS->x0.x1,&ANS->x0.x1,&scalar1_of_prime_exp_3);
	//x1
	Fp_set(&ANS->x1.x0.x0,&A->x1.x0.x0);
	Fp_set_neg(&ANS->x1.x0.x1,&A->x1.x0.x1);
	Fp2_mul(&ANS->x1.x0,&ANS->x1.x0,&scalar2_of_prime_exp_3);
	Fp_set(&ANS->x1.x1.x0,&A->x1.x1.x0);
	Fp_set_neg(&ANS->x1.x1.x1,&A->x1.x1.x1);
	Fp2_mul(&ANS->x1.x1,&ANS->x1.x1,&scalar1_of_prime_exp_3);
	Fp2_mul(&ANS->x1.x1,&ANS->x1.x1,&scalar2_of_prime_exp_3);
	//x2
	Fp_set(&tmp,&A->x2.x0.x0);
	Fp_set(&ANS->x2.x0.x0,&A->x2.x0.x1);
	Fp_set(&ANS->x2.x0.x1,&tmp);
	Fp_set(&tmp,&A->x2.x1.x0);
	Fp_set(&ANS->x2.x1.x0,&A->x2.x1.x1);
	Fp_set(&ANS->x2.x1.x1,&tmp);
	Fp2_mul(&ANS->x2.x1,&ANS->x2.x1,&scalar1_of_prime_exp_3);
	
	Fp_clear(&tmp);
}
void Fp12_frobenius_4(struct Fp12 *ANS,struct Fp12 *A){
	Fp4_set(&ANS->x0,&A->x0);
	Fp4_mul_mpz(&ANS->x1,&A->x1,scalar1_of_prime_exp_4.x0.x0);
	Fp4_mul_mpz(&ANS->x2,&A->x2,scalar2_of_prime_exp_4.x0.x0);
}
void Fp12_frobenius_6(struct Fp12 *ANS,struct Fp12 *A){
	Fp2_set(&ANS->x0.x0,&A->x0.x0);
	Fp2_set_neg(&ANS->x0.x1,&A->x0.x1);
	Fp2_set_neg(&ANS->x1.x0,&A->x1.x0);
	Fp2_set(&ANS->x1.x1,&A->x1.x1);
	Fp2_set(&ANS->x2.x0,&A->x2.x0);
	Fp2_set_neg(&ANS->x2.x1,&A->x2.x1);
}
void Fp12_frobenius_8(struct Fp12 *ANS,struct Fp12 *A){
	Fp4_set(&ANS->x0,&A->x0);
	Fp4_mul_mpz(&ANS->x1,&A->x1,scalar1_of_prime_exp_8.x0.x0);
	Fp4_mul_mpz(&ANS->x2,&A->x2,scalar2_of_prime_exp_8.x0.x0);
}
void Fp12_frobenius_10(struct Fp12 *ANS,struct Fp12 *A){	
	Fp2_set(&ANS->x0.x0,&A->x0.x0);
	Fp2_set_neg(&ANS->x0.x1,&A->x0.x1);
	Fp2_mul_mpz(&ANS->x1.x0,&A->x1.x0,scalar1_of_prime_exp_10.x0.x0);
	Fp2_set_neg(&ANS->x1.x1,&A->x1.x1);
	Fp2_mul_mpz(&ANS->x1.x1,&ANS->x1.x1,scalar1_of_prime_exp_10.x0.x0);
	Fp2_mul_mpz(&ANS->x2.x0,&A->x2.x0,scalar2_of_prime_exp_10.x0.x0);
	Fp2_set_neg(&ANS->x2.x1,&A->x2.x1);
	Fp2_mul_mpz(&ANS->x2.x1,&ANS->x2.x1,scalar2_of_prime_exp_10.x0.x0);
}
/*---------------------------------cmp----------------------------------*/
int Fp12_cmp(struct Fp12 *A,struct Fp12 *B){
	if(Fp4_cmp(&A->x0,&B->x0)==0 && Fp4_cmp(&A->x1,&B->x1)==0 && Fp4_cmp(&A->x2,&B->x2)==0){
		return 0;	
	}
	return 1;
}
int Fp12_cmp_ui(struct Fp12 *A,unsigned long int a){
	if(Fp4_cmp_ui(&A->x0,a)==0 && Fp4_cmp_ui(&A->x1,a)==0 && Fp4_cmp_ui(&A->x2,a)==0){
		return 0;
	}
	return 1;
}
int Fp12_cmp_mpz(struct Fp12 *A,mpz_t a){
	if(Fp4_cmp_mpz(&A->x0,a)==0 && Fp4_cmp_mpz(&A->x1,a)==0 && Fp4_cmp_mpz(&A->x2,a)==0){
		return 0;
	}
	return 1;
}
int Fp12_cmp_zero(struct Fp12 *A){
	if(Fp4_cmp_zero(&A->x0)==0 && Fp4_cmp_zero(&A->x1)==0 && Fp4_cmp_zero(&A->x2)==0){
		return 0;
	}
	return 1;
}
int Fp12_cmp_one(struct Fp12 *A){
	if(Fp4_cmp_one(&A->x0)==0 && Fp4_cmp_zero(&A->x1)==0 && Fp4_cmp_zero(&A->x2)==0){
		return 0;
	}
	return 1;
}
/*============================================================================*/
/* sparse                                                                     */
/*============================================================================*/
void Fp12_mul_100000001100_111111111111(struct Fp12 *ANS,struct Fp12 *A,struct Fp12 *B){
	struct Fp4 tmp00,tmp22,buf,t0,t1,t2;
	Fp4_init(&tmp00);
	Fp4_init(&tmp22);
	Fp4_init(&buf);
	Fp4_init(&t0);
	Fp4_init(&t1);
	Fp4_init(&t2);
	
	//set
	//Fp4_mul_1000_1111
	Fp4_mul_mpz(&tmp00,&B->x0,A->x0.x0.x0.x0);//x0*y0
	//Fp4_mul_1100_1111
	Fp2_mul(&tmp22.x0,&A->x2.x0,&B->x2.x0);//x2*y2
	Fp2_mul(&tmp22.x1,&A->x2.x0,&B->x2.x1);
	
	Fp4_add(&buf,&B->x0,&B->x1);//y0+y1
	//Fp4_mul_1000_1111
	Fp4_mul_mpz(&t0,&buf,A->x0.x0.x0.x0);//(x0+x1)(y0+y1)
	
	Fp4_add(&buf,&B->x1,&B->x2);//y1+y2
	//Fp4_mul_1100_1111
	Fp2_mul(&t1.x0,&A->x2.x0,&buf.x0);//(x1+x2)(y1+y2)
	Fp2_mul(&t1.x1,&A->x2.x0,&buf.x1);
	
	Fp_add(&t2.x0.x0,&A->x0.x0.x0,&A->x2.x0.x0);//x2+x0
	Fp_set(&t2.x0.x1,&A->x2.x0.x1);
	Fp4_add(&buf,&B->x0,&B->x2);//y2+y0
	//Fp4_mul_1100_1111
	Fp2_mul(&t2.x1,&t2.x0,&buf.x1);//(x2+x0)(y2+y0)
	Fp2_mul(&t2.x0,&t2.x0,&buf.x0);
	
	//x0
	Fp4_sub(&t1,&t1,&tmp22);//(x1+x2)(y1+y2)-x1y1-x2y2
	Fp4_mul_basis(&buf,&t1);
	Fp4_add(&ANS->x0,&tmp00,&buf);
	//x1
	Fp4_sub(&t0,&t0,&tmp00);
	Fp4_mul_basis(&buf,&tmp22);
	Fp4_add(&ANS->x1,&buf,&t0);
	//x2
	Fp4_sub(&t2,&t2,&tmp00);
	Fp4_sub(&ANS->x2,&t2,&tmp22);
	
	//clear
	Fp4_clear(&tmp00);
	Fp4_clear(&tmp22);
	Fp4_clear(&buf);
	Fp4_clear(&t0);
	Fp4_clear(&t1);
	Fp4_clear(&t2);
}
void Fp12_mul_101100000011_111111111111(struct Fp12 *ANS,struct Fp12 *A,struct Fp12 *B){
	struct Fp4 tmp00,tmp22,buf,t0,t1,t2;
	Fp4_init(&tmp00);
	Fp4_init(&tmp22);
	Fp4_init(&buf);
	Fp4_init(&t0);
	Fp4_init(&t1);
	Fp4_init(&t2);
	struct Fp2 tmp1,tmp2;
	Fp2_init(&tmp1);
	Fp2_init(&tmp2);
	
	//set
	//Fp4_mul_1011_1111
	Fp2_mul(&tmp2,&A->x0.x1,&B->x0.x1);	//x0*y0	//1
	Fp_add(&tmp1.x0,&A->x0.x1.x0,&A->x0.x0.x0);
	Fp_set(&tmp1.x1,&A->x0.x1.x1);
	Fp2_add(&tmp00.x1,&B->x0.x0,&B->x0.x1);
	Fp2_mul(&tmp00.x1,&tmp1,&tmp00.x1);			//2
	Fp2_mul_mpz(&tmp1,&B->x0.x0,A->x0.x0.x0.x0);
	Fp2_mul_basis(&tmp00.x0,&tmp2);
	Fp2_add(&tmp00.x0,&tmp00.x0,&tmp1);
	Fp2_sub(&tmp00.x1,&tmp00.x1,&tmp1);
	Fp2_sub(&tmp00.x1,&tmp00.x1,&tmp2);
	
	//Fp4_mul_0011_1111
	Fp2_mul(&tmp22.x0,&A->x2.x1,&B->x2.x1);//x2*y2	//3
	Fp2_mul_basis(&tmp22.x0,&tmp22.x0);
	Fp2_mul(&tmp22.x1,&A->x2.x1,&B->x2.x0);		//4
	
	Fp_set(&t0.x0.x0,&A->x0.x0.x0);//x0+x1
	Fp2_set(&t0.x1,&A->x0.x1);
	Fp4_add(&buf,&B->x0,&B->x1);//y0+y1
	//Fp4_mul_1011_1111
	Fp2_mul(&tmp2,&t0.x1,&buf.x1);//(x0+x1)(y0+y1)	//5
	Fp_add(&tmp1.x0,&t0.x1.x0,&t0.x0.x0);
	Fp_set(&tmp1.x1,&t0.x1.x1);
	Fp2_add(&t0.x1,&buf.x0,&buf.x1);
	Fp2_mul(&t0.x1,&tmp1,&t0.x1);				//6
	Fp2_mul_mpz(&tmp1,&buf.x0,t0.x0.x0.x0);
	Fp2_mul_basis(&t0.x0,&tmp2);
	Fp2_add(&t0.x0,&t0.x0,&tmp1);
	Fp2_sub(&t0.x1,&t0.x1,&tmp1);
	Fp2_sub(&t0.x1,&t0.x1,&tmp2);
	
	Fp4_add(&buf,&B->x1,&B->x2);//y1+y2
	//Fp4_mul_0011_1111
	Fp2_mul(&t1.x0,&A->x2.x1,&buf.x1);//(x1+x2)(y1+y2)	//7
	Fp2_mul_basis(&t1.x0,&t1.x0);
	Fp2_mul(&t1.x1,&A->x2.x1,&buf.x0);				//8
	
	Fp4_add(&t2,&A->x0,&A->x2);//x2+x0
	Fp4_add(&buf,&B->x0,&B->x2);//y2+y0
	
	//Fp4_mul_1011_1111
	Fp2_mul(&tmp2,&t2.x1,&buf.x1);//(x2+x0)(y2+y0)		//9
	Fp_add(&tmp1.x0,&t2.x1.x0,&t2.x0.x0);
	Fp_set(&tmp1.x1,&t2.x1.x1);
	Fp2_add(&t2.x1,&buf.x0,&buf.x1);
	Fp2_mul(&t2.x1,&tmp1,&t2.x1);					//10
	Fp2_mul_mpz(&tmp1,&buf.x0,t2.x0.x0.x0);
	Fp2_mul_basis(&t2.x0,&tmp2);
	Fp2_add(&t2.x0,&t2.x0,&tmp1);
	Fp2_sub(&t2.x1,&t2.x1,&tmp1);
	Fp2_sub(&t2.x1,&t2.x1,&tmp2);
	
	//x0
	Fp4_sub(&t1,&t1,&tmp22);//(x1+x2)(y1+y2)-x1y1-x2y2
	Fp4_mul_basis(&buf,&t1);
	Fp4_add(&ANS->x0,&tmp00,&buf);
	//x1
	Fp4_sub(&t0,&t0,&tmp00);
	Fp4_mul_basis(&buf,&tmp22);
	Fp4_add(&ANS->x1,&buf,&t0);
	//x2
	Fp4_sub(&t2,&t2,&tmp00);
	Fp4_sub(&ANS->x2,&t2,&tmp22);
	
	//clear
	Fp4_clear(&tmp00);
	Fp4_clear(&tmp22);
	Fp4_clear(&buf);
	Fp4_clear(&t0);
	Fp4_clear(&t1);
	Fp4_clear(&t2);
	Fp2_clear(&tmp1);
	Fp2_clear(&tmp2);
}

/*============================================================================*/
/* EFp                                                                        */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void EFp_init(struct EFp *P){
	Fp_init(&P->x);
	Fp_init(&P->y);
	P->flag=0;
}
/*---------------------------------set----------------------------------*/
void EFp_set(struct EFp *P,struct EFp *A){
	Fp_set(&P->x,&A->x);
	Fp_set(&P->y,&A->y);
	P->flag=A->flag;
}
void EFp_set_ui(struct EFp *P,unsigned long int a){
	Fp_set_ui(&P->x,a);
	Fp_set_ui(&P->y,a);
	P->flag=0;
}
void EFp_set_mpz(struct EFp *P,mpz_t a){
	Fp_set_mpz(&P->x,a);
	Fp_set_mpz(&P->y,a);
	P->flag=0;
}
void EFp_set_neg(struct EFp *P,struct EFp *A){
	Fp_set(&P->x,&A->x);
	Fp_set_neg(&P->y,&A->y);
	P->flag=A->flag;
}
/*---------------------------------clear--------------------------------*/
void EFp_clear(struct EFp *P){
	Fp_clear(&P->x);
	Fp_clear(&P->y);
}
/*---------------------------------print--------------------------------*/
void EFp_printf(struct EFp *P,char *name){
	printf("%s",name);
	if(P->flag==0){
		printf("(");
		Fp_printf(&P->x,"");
		printf(",");
		Fp_printf(&P->y,"");
		printf(")");
	}else{
		printf("0");
	}
}
/*-----------------------------rational point---------------------------*/
void EFp_rational_point(struct EFp *P){
	struct Fp buf1,buf2,R;
	Fp_init(&buf1);
	Fp_init(&buf2);
	Fp_init(&R);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	while(1){
		Fp_random(&P->x,state);
		Fp_mul(&buf1,&P->x,&P->x);
		Fp_mul(&buf2,&buf1,&P->x);
		Fp_mul_mpz(&buf1,&P->x,curve_parameter_A);
		Fp_add(&R,&buf1,&buf2);
		Fp_sub_mpz(&R,&R,curve_parameter_B);
		if(Fp_legendre(&R)==1){
			Fp_sqrt(&P->y,&R);
			break;
		}
	}
	
	Fp_clear(&buf1);
	Fp_clear(&buf2);
	Fp_clear(&R);
}
/*---------------------------------SCM----------------------------------*/
void EFp_ECD(struct EFp *ANS,struct EFp *P){
	if(Fp_cmp_ui(&P->y,0)==0){
		ANS->flag=1;
		return;
	}
	
	struct EFp Tmp;
	EFp_init(&Tmp);
	EFp_set(&Tmp,P);
	struct Fp Buf1,Buf2,C;
	Fp_init(&Buf1);
	Fp_init(&Buf2);
	Fp_init(&C);
	
	Fp_mul_ui(&Buf1,&Tmp.y,2);
	//Fp_inv(&Buf1,&Buf1);
	mpz_invert(Buf1.x0,Buf1.x0,prime);
	Fp_mul(&Buf2,&Tmp.x,&Tmp.x);
	Fp_mul_ui(&Buf2,&Buf2,3);
	Fp_add_mpz(&Buf2,&Buf2,curve_parameter_A);
	Fp_mul(&C,&Buf1,&Buf2);
	Fp_mul(&Buf1,&C,&C);
	Fp_mul_ui(&Buf2,&Tmp.x,2);
	Fp_sub(&ANS->x,&Buf1,&Buf2);
	Fp_sub(&Buf1,&Tmp.x,&ANS->x);
	Fp_mul(&Buf2,&C,&Buf1);
	Fp_sub(&ANS->y,&Buf2,&Tmp.y);
	
	//clear
	Fp_clear(&Buf1);
	Fp_clear(&Buf2);
	Fp_clear(&C);
	EFp_clear(&Tmp);
}
void EFp_ECA(struct EFp *ANS,struct EFp *P1,struct EFp *P2){
	if(P1->flag==1){
		EFp_set(ANS,P2);
		return;
	}else if(P2->flag==1){
		EFp_set(ANS,P1);
		return;
	}else if(Fp_cmp(&P1->x,&P2->x)==0){
		if(Fp_cmp(&P1->y,&P2->y)!=0){
			ANS->flag=1;
			return;
		}else{
			EFp_ECD(ANS,P1);
			return;
		}
	}
	
	struct EFp Tmp1,Tmp2;
	EFp_init(&Tmp1);
	EFp_set(&Tmp1,P1);
	EFp_init(&Tmp2);
	EFp_set(&Tmp2,P2);
	struct Fp Buf1,Buf2,C;
	Fp_init(&Buf1);
	Fp_init(&Buf2);
	Fp_init(&C);
	
	Fp_sub(&Buf1,&Tmp2.x,&Tmp1.x);
	//Fp_inv(&Buf1,&Buf1);
	mpz_invert(Buf1.x0,Buf1.x0,prime);
	Fp_sub(&Buf2,&Tmp2.y,&Tmp1.y);
	Fp_mul(&C,&Buf1,&Buf2);
	Fp_mul(&Buf1,&C,&C);
	Fp_sub(&Buf2,&Buf1,&Tmp1.x);
	Fp_sub(&ANS->x,&Buf2,&Tmp2.x);
	Fp_sub(&Buf1,&Tmp1.x,&ANS->x);
	Fp_mul(&Buf2,&C,&Buf1);
	Fp_sub(&ANS->y,&Buf2,&Tmp1.y);
		
	//clear	
	Fp_clear(&Buf1);
	Fp_clear(&Buf2);
	Fp_clear(&C);
	EFp_clear(&Tmp1);
	EFp_clear(&Tmp2);
}
void EFp_SCM(struct EFp *ANS,struct EFp *P,mpz_t R){
	if(mpz_cmp_ui(R,0)==0){
		ANS->flag=1;
		return;
	}else if(mpz_cmp_ui(R,1)==0){
		EFp_set(ANS,P);
		return;
	}
	
	struct EFp Tmp,next_P;
	EFp_init(&Tmp);
	EFp_set(&Tmp,P);
	EFp_init(&next_P);
	int i,length;
	length=(int)mpz_sizeinbase(R,2);
	char binary[length];
	mpz_get_str(binary,2,R);
	
	EFp_set(&next_P,&Tmp);
	for(i=1; binary[i]!='\0'; i++){
		EFp_ECD(&next_P,&next_P);
		if(binary[i]=='1'){
			EFp_ECA(&next_P,&next_P,&Tmp);
		}
	}
	
	EFp_set(ANS,&next_P);
	
	EFp_clear(&next_P);
	EFp_clear(&Tmp);
}
void EFp_skew_frobenius(struct EFp *ANS,struct EFp *A){
	Fp_mul(&ANS->x,&A->x,&inv_CNR1);
	Fp_set_neg(&ANS->y,&A->y);
}

/*============================================================================*/
/* EFp2                                                                       */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void EFp2_init(struct EFp2 *P){
	Fp2_init(&P->x);
	Fp2_init(&P->y);
	P->flag=0;
}
/*---------------------------------set----------------------------------*/
void EFp2_set(struct EFp2 *P,struct EFp2 *A){
	Fp2_set(&P->x,&A->x);
	Fp2_set(&P->y,&A->y);
	P->flag=A->flag;
}
void EFp2_set_ui(struct EFp2 *P,unsigned long int a){
	Fp2_set_ui(&P->x,a);
	Fp2_set_ui(&P->y,a);
	P->flag=0;
}
void EFp2_set_mpz(struct EFp2 *P,mpz_t a){
	Fp2_set_mpz(&P->x,a);
	Fp2_set_mpz(&P->y,a);
	P->flag=0;
}
void EFp2_set_neg(struct EFp2 *ANS,struct EFp2 *P){
	Fp2_set(&ANS->x,&P->x);
	Fp2_set_neg(&ANS->y,&P->y);
	ANS->flag=P->flag;
}
/*---------------------------------clear--------------------------------*/
void EFp2_clear(struct EFp2 *P){
	Fp2_clear(&P->x);
	Fp2_clear(&P->y);
}
/*---------------------------------print--------------------------------*/
void EFp2_printf(struct EFp2 *P,char *name){
	printf("%s",name);
	if(P->flag==0){
		printf("(");
		Fp2_printf(&P->x,"X");
		printf(",");
		Fp2_printf(&P->y,"Y");
		printf(")");
	}else{
		printf("0");
	}
}
/*-----------------------------rational point---------------------------*/
void EFp2_rational_point(struct EFp2 *P){
	struct Fp2 buf1,buf2,R;
	Fp2_init(&buf1);
	Fp2_init(&buf2);
	Fp2_init(&R);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	while(1){
		Fp2_random(&P->x,state);
		Fp2_mul(&buf1,&P->x,&P->x);
		Fp2_mul(&buf2,&buf1,&P->x);
		Fp2_mul_mpz(&buf1,&P->x,curve_parameter_A);
		Fp2_add(&R,&buf1,&buf2);
		mpz_sub(R.x0.x0,R.x0.x0,curve_parameter_B);
		if(Fp2_legendre(&R)==1){
			Fp2_sqrt(&P->y,&R);
			break;
		}
	}
	
	Fp2_clear(&buf1);
	Fp2_clear(&buf2);
	Fp2_clear(&R);
}
/*---------------------------------SCM----------------------------------*/
void EFp2_ECD(struct EFp2 *ANS,struct EFp2 *P){
	if(Fp2_cmp_ui(&P->y,0)==0){
		ANS->flag=1;
		return;
	}
	
	struct EFp2 Tmp;
	EFp2_init(&Tmp);
	EFp2_set(&Tmp,P);
	struct Fp2 Buf1,Buf2,C;
	Fp2_init(&Buf1);
	Fp2_init(&Buf2);
	Fp2_init(&C);
	
	Fp2_mul_ui(&Buf1,&Tmp.y,2);
	
	Fp2_inv(&Buf1,&Buf1);
	Fp2_mul(&Buf2,&Tmp.x,&Tmp.x);
	Fp2_mul_ui(&Buf2,&Buf2,3);
	mpz_add(Buf2.x0.x0,Buf2.x0.x0,curve_parameter_A);
	Fp2_mul(&C,&Buf1,&Buf2);
	
	Fp2_squaring(&Buf1,&C);
	Fp2_mul_ui(&Buf2,&Tmp.x,2);
	Fp2_sub(&ANS->x,&Buf1,&Buf2);
	
	Fp2_sub(&Buf1,&Tmp.x,&ANS->x);
	Fp2_mul(&Buf2,&C,&Buf1);
	Fp2_sub(&ANS->y,&Buf2,&Tmp.y);
	
	Fp2_clear(&Buf1);
	Fp2_clear(&Buf2);
	Fp2_clear(&C);
	EFp2_clear(&Tmp);
}
void EFp2_ECA(struct EFp2 *ANS,struct EFp2 *P1,struct EFp2 *P2){
	struct timeval t0,t1;
	if(P1->flag==1){
		EFp2_set(ANS,P2);
		return;
	}else if(P2->flag==1){
		EFp2_set(ANS,P1);
		return;
	}else if(Fp2_cmp(&P1->x,&P2->x)==0){
		if(Fp2_cmp(&P1->y,&P2->y)!=0){
			ANS->flag=1;
			return;
		}else{
			EFp2_ECD(ANS,P1);
			return;
		}
	}
	
	struct EFp2 Tmp1,Tmp2;
	EFp2_init(&Tmp1);
	EFp2_set(&Tmp1,P1);
	EFp2_init(&Tmp2);
	EFp2_set(&Tmp2,P2);
	struct Fp2 Buf1,Buf2,C;
	Fp2_init(&Buf1);
	Fp2_init(&Buf2);
	Fp2_init(&C);
	
	Fp2_sub(&Buf1,&Tmp2.x,&Tmp1.x);
	Fp2_inv(&Buf1,&Buf1);
	Fp2_sub(&Buf2,&Tmp2.y,&Tmp1.y);
	Fp2_mul(&C,&Buf1,&Buf2);
	Fp2_squaring(&Buf1,&C);
	Fp2_sub(&Buf2,&Buf1,&Tmp1.x);
	Fp2_sub(&ANS->x,&Buf2,&Tmp2.x);
	Fp2_sub(&Buf1,&Tmp1.x,&ANS->x);
	Fp2_mul(&Buf2,&C,&Buf1);
	Fp2_sub(&ANS->y,&Buf2,&Tmp1.y);
		
	//clear	
	Fp2_clear(&Buf1);
	Fp2_clear(&Buf2);
	Fp2_clear(&C);
	EFp2_clear(&Tmp1);
	EFp2_clear(&Tmp2);
}
void EFp2_SCM(struct EFp2 *ANS,struct EFp2 *P,mpz_t R){
	if(mpz_cmp_ui(R,0)==0){
		ANS->flag=1;
		return;
	}else if(mpz_cmp_ui(R,1)==0){
		EFp2_set(ANS,P);
		return;
	}
	
	struct EFp2 Tmp,next_P;
	EFp2_init(&Tmp);
	EFp2_set(&Tmp,P);
	EFp2_init(&next_P);
	int i,length;
	length=(int)mpz_sizeinbase(R,2);
	char binary[length];
	mpz_get_str(binary,2,R);
	
	EFp2_set(&next_P,&Tmp);
	for(i=1; binary[i]!='\0'; i++){
		EFp2_ECD(&next_P,&next_P);
		if(binary[i]=='1'){
			EFp2_ECA(&next_P,&next_P,&Tmp);
		}
	}
	EFp2_set(ANS,&next_P);
	
	EFp2_clear(&next_P);
	EFp2_clear(&Tmp);
}
void EFp2_frobenius_1(struct EFp2 *ANS,struct EFp2 *P){
	Fp2_frobenius_1(&ANS->x,&P->x);
	Fp2_frobenius_1(&ANS->y,&P->y);
}
void EFp2_frobenius_2(struct EFp2 *ANS,struct EFp2 *P){
	Fp2_frobenius_2(&ANS->x,&P->x);
	Fp2_frobenius_2(&ANS->y,&P->y);
}
void EFp2_skew_frobenius_1(struct EFp2 *ANS,struct EFp2 *A){
	//x
	Fp2_frobenius_1(&ANS->x,&A->x);
	Fp2_mul(&ANS->x,&ANS->x,&x_of_skew_frobenius_1);
	//y
	Fp2_frobenius_1(&ANS->y,&A->y);
	Fp2_mul(&ANS->y,&ANS->y,&y_of_skew_frobenius_1);
}
void EFp2_skew_frobenius_2(struct EFp2 *ANS,struct EFp2 *A){
	//x
	Fp2_frobenius_2(&ANS->x,&A->x);
	Fp2_mul(&ANS->x,&ANS->x,&x_of_skew_frobenius_2);
	//y
	Fp2_frobenius_2(&ANS->y,&A->y);
	Fp2_mul(&ANS->y,&ANS->y,&y_of_skew_frobenius_2);
}
void EFp2_skew_frobenius_3(struct EFp2 *ANS,struct EFp2 *A){
	//x
	Fp2_frobenius_3(&ANS->x,&A->x);
	Fp2_mul(&ANS->x,&ANS->x,&x_of_skew_frobenius_3);
	//y
	Fp2_frobenius_3(&ANS->y,&A->y);
	Fp2_mul(&ANS->y,&ANS->y,&y_of_skew_frobenius_3);
}
void EFp2_skew_frobenius_10(struct EFp2 *ANS,struct EFp2 *A){
	//x
	Fp2_frobenius_10(&ANS->x,&A->x);
	Fp2_mul(&ANS->x,&ANS->x,&x_of_skew_frobenius_10);
	//y
	Fp2_frobenius_10(&ANS->y,&A->y);
	Fp2_mul(&ANS->y,&ANS->y,&y_of_skew_frobenius_10);
}
/*============================================================================*/
/* EFp4                                                                       */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void EFp4_init(struct EFp4 *P){
	Fp4_init(&P->x);
	Fp4_init(&P->y);
	P->flag=0;
}
void EFp4_set(struct EFp4 *P,struct EFp4 *A){
	Fp4_set(&P->x,&A->x);
	Fp4_set(&P->y,&A->y);
	P->flag=A->flag;
}
void EFp4_set_ui(struct EFp4 *P,unsigned long int a){
	Fp4_set_ui(&P->x,a);
	Fp4_set_ui(&P->y,a);
	P->flag=0;
}
void EFp4_set_mpz(struct EFp4 *P,mpz_t a){
	Fp4_set_mpz(&P->x,a);
	Fp4_set_mpz(&P->y,a);
	P->flag=0;
}
void EFp4_set_neg(struct EFp4 *P,struct EFp4 *A){
	Fp4_set(&P->x,&A->x);
	Fp4_set_neg(&P->y,&A->y);
	P->flag=A->flag;
}
/*---------------------------------clear--------------------------------*/
void EFp4_clear(struct EFp4 *P){
	Fp4_clear(&P->x);
	Fp4_clear(&P->y);
}
/*---------------------------------print--------------------------------*/
void EFp4_printf(struct EFp4 *P,char *name){
	printf("%s",name);
	if(P->flag==0){
		printf("(");
		Fp4_printf(&P->x,"X");
		printf(",");
		Fp4_printf(&P->y,"Y");
		printf(")");
	}else{
		printf("0");
	}
}
/*-----------------------------rational point---------------------------*/
void EFp4_rational_point(struct EFp4 *P){
	struct Fp4 buf1,buf2,R;
	Fp4_init(&buf1);
	Fp4_init(&buf2);
	Fp4_init(&R);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	while(1){
		Fp4_random(&P->x,state);
		Fp4_mul(&buf1,&P->x,&P->x);
		Fp4_mul(&buf2,&buf1,&P->x);
		Fp4_mul_mpz(&buf1,&P->x,curve_parameter_A);
		Fp4_add(&R,&buf1,&buf2);
		mpz_sub(R.x0.x0.x0,R.x0.x0.x0,curve_parameter_B);
		if(Fp4_legendre(&R)==1){
			Fp4_sqrt(&P->y,&R);
			break;
		}
	}
	
	Fp4_clear(&buf1);
	Fp4_clear(&buf2);
	Fp4_clear(&R);
}
/*---------------------------------SCM----------------------------------*/
void EFp4_ECD(struct EFp4 *ANS,struct EFp4 *P){
	if(Fp4_cmp_ui(&P->y,0)==0){
		ANS->flag=1;
		return;
	}
	
	struct EFp4 Tmp;
	EFp4_init(&Tmp);
	EFp4_set(&Tmp,P);
	struct Fp4 Buf1,Buf2,C;
	Fp4_init(&Buf1);
	Fp4_init(&Buf2);
	Fp4_init(&C);
	
	Fp4_mul_ui(&Buf1,&Tmp.y,2);
	
	Fp4_inv(&Buf1,&Buf1);
	Fp4_mul(&Buf2,&Tmp.x,&Tmp.x);
	Fp4_mul_ui(&Buf2,&Buf2,3);
	mpz_add(Buf2.x0.x0.x0,Buf2.x0.x0.x0,curve_parameter_A);
	Fp4_mul(&C,&Buf1,&Buf2);
	Fp4_mul(&Buf1,&C,&C);
	Fp4_mul_ui(&Buf2,&Tmp.x,2);
	Fp4_sub(&ANS->x,&Buf1,&Buf2);
	Fp4_sub(&Buf1,&Tmp.x,&ANS->x);
	Fp4_mul(&Buf2,&C,&Buf1);
	Fp4_sub(&ANS->y,&Buf2,&Tmp.y);
	
	Fp4_clear(&Buf1);
	Fp4_clear(&Buf2);
	Fp4_clear(&C);
	EFp4_clear(&Tmp);
}
void EFp4_ECA(struct EFp4 *ANS,struct EFp4 *P1,struct EFp4 *P2){
	if(P1->flag==1){
		EFp4_set(ANS,P2);
		return;
	}else if(P2->flag==1){
		EFp4_set(ANS,P1);
		return;
	}else if(Fp4_cmp(&P1->x,&P2->x)==0){
		if(Fp4_cmp(&P1->y,&P2->y)!=0){
			ANS->flag=1;
			return;
		}else{
			EFp4_ECD(ANS,P1);
			return;
		}
	}
	
	struct EFp4 Tmp1,Tmp2;
	EFp4_init(&Tmp1);
	EFp4_set(&Tmp1,P1);
	EFp4_init(&Tmp2);
	EFp4_set(&Tmp2,P2);
	struct Fp4 Buf1,Buf2,C;
	Fp4_init(&Buf1);
	Fp4_init(&Buf2);
	Fp4_init(&C);
	
	Fp4_sub(&Buf1,&Tmp2.x,&Tmp1.x);
	Fp4_inv(&Buf1,&Buf1);
	Fp4_sub(&Buf2,&Tmp2.y,&Tmp1.y);
	Fp4_mul(&C,&Buf1,&Buf2);
	Fp4_mul(&Buf1,&C,&C);
	Fp4_sub(&Buf2,&Buf1,&Tmp1.x);
	Fp4_sub(&ANS->x,&Buf2,&Tmp2.x);
	Fp4_sub(&Buf1,&Tmp1.x,&ANS->x);
	Fp4_mul(&Buf2,&C,&Buf1);
	Fp4_sub(&ANS->y,&Buf2,&Tmp1.y);
		
	//clear	
	Fp4_clear(&Buf1);
	Fp4_clear(&Buf2);
	Fp4_clear(&C);
	EFp4_clear(&Tmp1);
	EFp4_clear(&Tmp2);
}
void EFp4_SCM(struct EFp4 *ANS,struct EFp4 *P,mpz_t R){
	if(mpz_cmp_ui(R,0)==0){
		ANS->flag=1;
		return;
	}else if(mpz_cmp_ui(R,1)==0){
		EFp4_set(ANS,P);
		return;
	}
	
	struct EFp4 Tmp,next_P;
	EFp4_init(&Tmp);
	EFp4_set(&Tmp,P);
	EFp4_init(&next_P);
	int i,length;
	length=(int)mpz_sizeinbase(R,2);
	char binary[length];
	mpz_get_str(binary,2,R);
	mpz_t order,buf;
	mpz_init(order);
	mpz_init(buf);
	
	EFp4_set(&next_P,&Tmp);
	for(i=1; binary[i]!='\0'; i++){
		EFp4_ECD(&next_P,&next_P);
		if(binary[i]=='1'){
			EFp4_ECA(&next_P,&next_P,&Tmp);
		}
	}
	
	EFp4_set(ANS,&next_P);
	
	EFp4_clear(&next_P);
	EFp4_clear(&Tmp);
}

/*============================================================================*/
/* EFp12                                                                      */
/*============================================================================*/
/*---------------------------------init---------------------------------*/
void EFp12_init(struct EFp12 *P){
	Fp12_init(&P->x);
	Fp12_init(&P->y);
	P->flag=0;
}
/*---------------------------------set----------------------------------*/
void EFp12_set(struct EFp12 *P,struct EFp12 *A){
	Fp12_set(&P->x,&A->x);
	Fp12_set(&P->y,&A->y);
	P->flag=A->flag;
}
void EFp12_set_ui(struct EFp12 *P,unsigned long int a){
	Fp12_set_ui(&P->x,a);
	Fp12_set_ui(&P->y,a);
	P->flag=0;
}
void EFp12_set_mpz(struct EFp12 *P,mpz_t a){
	Fp12_set_mpz(&P->x,a);
	Fp12_set_mpz(&P->y,a);
	P->flag=0;
}
void EFp12_set_neg(struct EFp12 *P,struct EFp12 *A){
	Fp12_set(&P->x,&A->x);
	Fp12_set_neg(&P->y,&A->y);
	P->flag=A->flag;
}
/*---------------------------------clear---------------------------------*/
void EFp12_clear(struct EFp12 *P){
	Fp12_clear(&P->x);
	Fp12_clear(&P->y);	
}
/*---------------------------------print---------------------------------*/
void EFp12_printf(struct EFp12 *P,char *name){
	printf("%s",name);
	if(P->flag==0){
		printf("(");
		Fp12_printf(&P->x,"X");
		printf("\n");
		Fp12_printf(&P->y,"Y");
		printf(")");
	}else{
		printf("0");
	}
}
/*-----------------------------rational point---------------------------*/
void EFp12_rational_point(struct EFp12 *P){
	struct Fp12 buf1,buf2,R;
	Fp12_init(&buf1);
	Fp12_init(&buf2);
	Fp12_init(&R);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	
	while(1){
		Fp12_random(&P->x,state);
		Fp12_squaring(&buf1,&P->x);
		Fp12_mul(&buf2,&buf1,&P->x);
		Fp12_mul_mpz(&buf1,&P->x,curve_parameter_A);
		Fp12_add(&R,&buf1,&buf2);
		mpz_sub(R.x0.x0.x0.x0,R.x0.x0.x0.x0,curve_parameter_B);
		if(Fp12_legendre(&R)==1){
			Fp12_sqrt(&P->y,&R);
			break;
		}
	}
	
	Fp12_clear(&buf1);
	Fp12_clear(&buf2);
	Fp12_clear(&R);
}
void EFp12_generate_G1(struct EFp12 *P){
	struct EFp g1;
	EFp_init(&g1);
	
	EFp_rational_point(&g1);
	EFp12_set_ui(P,0);
	Fp_set(&P->x.x0.x0.x0,&g1.x);
	Fp_set(&P->y.x0.x0.x0,&g1.y);
	P->flag=g1.flag;
	
	EFp_clear(&g1);
}
void EFp12_generate_G2(struct EFp12 *Q){
	struct EFp12 random_P,P,frobenius_P;
	EFp12_init(&random_P);
	EFp12_init(&P);
	EFp12_init(&frobenius_P);
	mpz_t exp;
	mpz_init(exp);
	
	EFp12_rational_point(&random_P);
	mpz_pow_ui(exp,EFp_order,2);
	mpz_tdiv_q(exp,EFp12_total,exp);
	EFp12_SCM(&P,&random_P,exp);
	EFp12_frobenius(&frobenius_P,&P);
	EFp12_set_neg(&P,&P);
	EFp12_ECA(Q,&P,&frobenius_P);
	
	mpz_clear(exp);
	EFp12_clear(&random_P);
	EFp12_clear(&P);
	EFp12_clear(&frobenius_P);
}
/*---------------------------------SCM----------------------------------*/
void EFp12_ECD(struct EFp12 *ANS,struct EFp12 *P){
	if(Fp12_cmp_ui(&P->y,0)==0){
		ANS->flag=1;
		return;
	}
	
	struct EFp12 Tmp;
	EFp12_init(&Tmp);
	EFp12_set(&Tmp,P);
	struct Fp12 Buf1,Buf2,C;
	Fp12_init(&Buf1);
	Fp12_init(&Buf2);
	Fp12_init(&C);
	
	Fp12_mul_ui(&Buf1,&Tmp.y,2);
	Fp12_inv(&Buf1,&Buf1);
	//Fp12_mul(&Buf2,&Tmp.x,&Tmp.x);
	Fp12_squaring(&Buf2,&Tmp.x);
	Fp12_mul_ui(&Buf2,&Buf2,3);
	mpz_add(Buf2.x0.x0.x0.x0,Buf2.x0.x0.x0.x0,curve_parameter_A);
	Fp12_mul(&C,&Buf1,&Buf2);
	//Fp12_mul(&Buf1,&C,&C);
	Fp12_squaring(&Buf1,&C);
	Fp12_mul_ui(&Buf2,&Tmp.x,2);
	Fp12_sub(&ANS->x,&Buf1,&Buf2);
	Fp12_sub(&Buf1,&Tmp.x,&ANS->x);
	Fp12_mul(&Buf2,&C,&Buf1);
	Fp12_sub(&ANS->y,&Buf2,&Tmp.y);
	
	Fp12_clear(&Buf1);
	Fp12_clear(&Buf2);
	Fp12_clear(&C);
	EFp12_clear(&Tmp);
}
void EFp12_ECA(struct EFp12 *ANS,struct EFp12 *P1,struct EFp12 *P2){
	if(P1->flag==1){
		EFp12_set(ANS,P2);
		return;
	}else if(P2->flag==1){
		EFp12_set(ANS,P1);
		return;
	}else if(Fp12_cmp(&P1->x,&P2->x)==0){
		if(Fp12_cmp(&P1->y,&P2->y)!=0){
			ANS->flag=1;
			return;
		}else{
			EFp12_ECD(ANS,P1);
			return;
		}
	}
	
	struct EFp12 Tmp1,Tmp2;
	EFp12_init(&Tmp1);
	EFp12_set(&Tmp1,P1);
	EFp12_init(&Tmp2);
	EFp12_set(&Tmp2,P2);
	struct Fp12 Buf1,Buf2,C;
	Fp12_init(&Buf1);
	Fp12_init(&Buf2);
	Fp12_init(&C);
	
	Fp12_sub(&Buf1,&Tmp2.x,&Tmp1.x);
	Fp12_inv(&Buf1,&Buf1);
	Fp12_sub(&Buf2,&Tmp2.y,&Tmp1.y);
	Fp12_mul(&C,&Buf1,&Buf2);
	//Fp12_mul(&Buf1,&C,&C);
	Fp12_squaring(&Buf1,&C);
	Fp12_sub(&Buf2,&Buf1,&Tmp1.x);
	Fp12_sub(&ANS->x,&Buf2,&Tmp2.x);
	Fp12_sub(&Buf1,&Tmp1.x,&ANS->x);
	Fp12_mul(&Buf2,&C,&Buf1);
	Fp12_sub(&ANS->y,&Buf2,&Tmp1.y);
		
	//clear	
	Fp12_clear(&Buf1);
	Fp12_clear(&Buf2);
	Fp12_clear(&C);
	EFp12_clear(&Tmp1);
	EFp12_clear(&Tmp2);
}
void EFp12_SCM(struct EFp12 *ANS,struct EFp12 *P,mpz_t R){
	if(mpz_cmp_ui(R,0)==0){
		ANS->flag=1;
		return;
	}else if(mpz_cmp_ui(R,1)==0){
		EFp12_set(ANS,P);
		return;
	}
	
	struct EFp12 Tmp,next_P;
	EFp12_init(&Tmp);
	EFp12_set(&Tmp,P);
	EFp12_init(&next_P);
	int i,length;
	length=(int)mpz_sizeinbase(R,2);
	char binary[length];
	mpz_get_str(binary,2,R);
	
	EFp12_set(&next_P,&Tmp);
	for(i=1; binary[i]!='\0'; i++){
		EFp12_ECD(&next_P,&next_P);
		if(binary[i]=='1'){
			EFp12_ECA(&next_P,&next_P,&Tmp);
		}
	}
	EFp12_set(ANS,&next_P);
	
	EFp12_clear(&next_P);
	EFp12_clear(&Tmp);
}
void EFp12_G1_SCM_normal(struct EFp12 *ANS,struct EFp12 *P,mpz_t S){
	struct EFp tmp_P;
	EFp_init(&tmp_P);
	
	Fp_set(&tmp_P.x,&P->x.x0.x0.x0);
	Fp_set(&tmp_P.y,&P->y.x0.x0.x0);
	tmp_P.flag=P->flag;
	
	EFp_SCM(&tmp_P,&tmp_P,S);
	
	Fp12_set_ui(&ANS->x,0);
	Fp12_set_ui(&ANS->y,0);
	Fp_set(&ANS->x.x0.x0.x0,&tmp_P.x);
	Fp_set(&ANS->y.x0.x0.x0,&tmp_P.y);
	
	EFp_clear(&tmp_P);
}
void EFp12_G1_SCM(struct EFp12 *ANS,struct EFp12 *P,mpz_t S){
	//struct timeval t0,t1;
	struct EFp tmp_P,skew_P,add_R,next_P,test;
	EFp_init(&tmp_P);
	EFp_init(&skew_P);
	EFp_init(&add_R);
	EFp_init(&next_P);
	EFp_init(&test);
	mpz_t s1,s2,s3,s4,s5,V1,V2,buf,A,B;
	mpz_init(s1);
	mpz_init(s2);
	mpz_init(s3);
	mpz_init(s4);
	mpz_init(s5);
	mpz_init(V1);
	mpz_init(V2);
	mpz_init(buf);
	mpz_init(A);
	mpz_init(B);
	int i,length_A,length_B,loop_length;
	
	//gettimeofday(&t0,NULL);
	//set
	Fp_set(&tmp_P.x,&P->x.x0.x0.x0);	//set tmp_P
	Fp_set(&tmp_P.y,&P->y.x0.x0.x0);
	tmp_P.flag=P->flag;
	EFp_skew_frobenius(&skew_P,&tmp_P);	//set skew_P
	
	//set V1
	mpz_mul(V1,mother_parameter,mother_parameter);
	mpz_mul_ui(V1,V1,6);
	mpz_mul_ui(buf,mother_parameter,4);
	mpz_add(V1,V1,buf);
	mpz_add_ui(V1,V1,1);
	//set V2
	mpz_add(V2,mother_parameter,mother_parameter);
	mpz_add_ui(V2,V2,1);
	mpz_tdiv_qr(s1,s2,S,V1);	//s1,s2
	mpz_mul(buf,V2,s1);		//s3,s4
	mpz_tdiv_qr(s3,s4,buf,V1);
	mpz_mul(s5,V2,s3);		//s5
	mpz_add(A,s4,s5);			//A
	mpz_mod(A,A,EFp_order);
	mpz_sub(B,s2,s5);			//B
	mpz_mod(B,B,EFp_order);
	
	//binary A
	length_A=(int)mpz_sizeinbase(A,2);
	//printf("G1 length_A:%d\n",length_A);
	//binary B
	length_B=(int)mpz_sizeinbase(B,2);
	if(length_B>400){
		//printf("neg patern\n");
		mpz_sub(B,EFp_order,B);
		length_B=(int)mpz_sizeinbase(B,2);
		EFp_set_neg(&tmp_P,&tmp_P);
	}
	//printf("G1 length_B:%d\n",length_B);
	
	//add_R
	EFp_ECA(&add_R,&tmp_P,&skew_P);	//set add_R
	
	//set binary
	if(length_A>length_B){
		loop_length=length_A;
	}else{
		loop_length=length_B;
	}
	char binary_A[loop_length+1];
	char binary_B[loop_length+1];
	if(length_A>length_B){
		char binary_buf[length_B+1];
		mpz_get_str(binary_buf,2,B);
		mpz_get_str(binary_A,2,A);
		memset(binary_B,'0',sizeof(binary_B));
		memmove(binary_B+length_A-length_B,binary_buf,sizeof(binary_buf));
		//set next_P
		EFp_set(&next_P,&skew_P);
	}else if(length_A<length_B){
		loop_length=length_B;
		mpz_get_str(binary_B,2,B);
		char binary_buf[length_A+1];
		mpz_get_str(binary_buf,2,A);
		memset(binary_A,'0',sizeof(binary_A));
		memmove(binary_A+length_B-length_A,binary_buf,sizeof(binary_buf));
		//set next_P
		EFp_set(&next_P,&tmp_P);
	}else{
		mpz_get_str(binary_A,2,A);
		mpz_get_str(binary_B,2,B);
		//set next_P
		EFp_set(&next_P,&add_R);
	}
	//gettimeofday(&t1,NULL);
	//printf("set time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	//gettimeofday(&t0,NULL);
	//SCM
	for(i=1; i<loop_length; i++){
		EFp_ECD(&next_P,&next_P);
		if(binary_A[i] == '0' && binary_B[i] == '1'){
			EFp_ECA(&next_P,&next_P,&tmp_P);
		}else if(binary_A[i] == '1' && binary_B[i] == '0'){
			EFp_ECA(&next_P,&next_P,&skew_P);
		}else if(binary_A[i] == '1' && binary_B[i] == '1'){
			EFp_ECA(&next_P,&next_P,&add_R);
		}
	}
	//gettimeofday(&t1,NULL);
	//printf("loop time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	Fp12_set_ui(&ANS->x,0);
	Fp12_set_ui(&ANS->y,0);
	Fp_set(&ANS->x.x0.x0.x0,&next_P.x);
	Fp_set(&ANS->y.x0.x0.x0,&next_P.y);
	ANS->flag=next_P.flag;
	
	mpz_clear(s1);
	mpz_clear(s2);
	mpz_clear(s3);
	mpz_clear(s4);
	mpz_clear(s5);
	mpz_clear(V1);
	mpz_clear(V2);
	mpz_clear(buf);
	mpz_clear(A);
	mpz_clear(B);
	EFp_clear(&test);
	EFp_clear(&tmp_P);
	EFp_clear(&skew_P);
	EFp_clear(&add_R);
	EFp_clear(&next_P);
}
void EFp12_G2_SCM_normal(struct EFp12 *ANS,struct EFp12 *Q,mpz_t S){
	struct EFp2 twisted_Q;
	EFp2_init(&twisted_Q);
	
	EFp12_to_EFp2(&twisted_Q,Q);
	EFp2_SCM(&twisted_Q,&twisted_Q,S);
	EFp2_to_EFp12(ANS,&twisted_Q);
	
	EFp2_clear(&twisted_Q);
}
void EFp12_G2_SCM_2div(struct EFp12 *ANS,struct EFp12 *Q,mpz_t S){
	//struct timeval t0,t1;
	struct EFp12 Buf;
	EFp12_init(&Buf);
	struct EFp2 twisted_Q,frobenius_Q,add_R,next_Q;
	EFp2_init(&twisted_Q);
	EFp2_init(&frobenius_Q);
	EFp2_init(&add_R);
	EFp2_init(&next_Q);
	mpz_t A,B,buf;
	mpz_init(A);
	mpz_init(B);
	mpz_init(buf);
	int i,length_A,length_B,loop_length;
	
	//gettimeofday(&t0,NULL);
	//set
	EFp12_to_EFp2(&twisted_Q,Q);				//twisted_Q
	EFp12_frobenius(&Buf,Q);
	EFp12_to_EFp2(&frobenius_Q,&Buf);			//frobenius_Q
	EFp2_ECA(&add_R,&twisted_Q,&frobenius_Q);		//add_R
	
	//A,B
	mpz_sub_ui(buf,trace_t,1);
	mpz_tdiv_qr(A,B,S,buf);
	
	//binary A
	length_A=(int)mpz_sizeinbase(A,2);
	//printf("G2 length_A:%d\n",length_A);
	//binary B
	length_B=(int)mpz_sizeinbase(B,2);
	//printf("G2 length_B:%d\n",length_B);
	//printf("\n");
	
	//set binary
	if(length_A>length_B){
		loop_length=length_A;
	}else{
		loop_length=length_B;
	}
	char binary_A[loop_length+1];
	char binary_B[loop_length+1];
	if(length_A>length_B){
		char binary_buf[length_B+1];
		mpz_get_str(binary_buf,2,B);
		mpz_get_str(binary_A,2,A);
		memset(binary_B,'0',sizeof(binary_B));
		memmove(binary_B+length_A-length_B,binary_buf,sizeof(binary_buf));
		//set next_Q
		EFp2_set(&next_Q,&frobenius_Q);
	}else if(length_A<length_B){
		mpz_get_str(binary_B,2,B);
		char binary_buf[length_A+1];
		mpz_get_str(binary_buf,2,A);
		memset(binary_A,'0',sizeof(binary_A));
		memmove(binary_A+length_B-length_A,binary_buf,sizeof(binary_buf));
		//set next_Q
		EFp2_set(&next_Q,&twisted_Q);
	}else{
		mpz_get_str(binary_A,2,A);
		mpz_get_str(binary_B,2,B);
		//set next_Q
		EFp2_set(&next_Q,&add_R);
	}
	//gettimeofday(&t1,NULL);
	//printf("set time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	//gettimeofday(&t0,NULL);
	//SCM
	for(i=1; i<loop_length; i++){
		EFp2_ECD(&next_Q,&next_Q);
		if(binary_A[i] == '0' && binary_B[i] == '1'){
			EFp2_ECA(&next_Q,&next_Q,&twisted_Q);
		}else if(binary_A[i] == '1' && binary_B[i] == '0'){
			EFp2_ECA(&next_Q,&next_Q,&frobenius_Q);
		}else if(binary_A[i] == '1' && binary_B[i] == '1'){
			EFp2_ECA(&next_Q,&next_Q,&add_R);
		}
	}
	//gettimeofday(&t1,NULL);
	//printf("set time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	EFp2_to_EFp12(ANS,&next_Q);
	ANS->flag=next_Q.flag;
	
	mpz_clear(A);
	mpz_clear(B);
	mpz_clear(buf);
	EFp2_clear(&twisted_Q);
	EFp2_clear(&frobenius_Q);
	EFp2_clear(&add_R);
	EFp2_clear(&next_Q);
	EFp12_clear(&Buf);
}
void EFp12_G2_SCM_4div(struct EFp12 *ANS,struct EFp12 *Q,mpz_t S){
	//struct timeval t0,t1;
	int i,length_s[4],loop_length;
	struct EFp12 Test;
	EFp12_init(&Test);
	struct EFp2 next_twisted_Q,twisted_Q,twisted_Q_6x,twisted_Q_6xx,twisted_Q_36xxx,skew_Q,skew_Q_neg,skew_Q_puls1,minus_skew_Q_puls1,buf_Q;
	EFp2_init(&next_twisted_Q);
	EFp2_init(&twisted_Q);
	EFp2_init(&twisted_Q_6x);
	EFp2_init(&twisted_Q_6xx);
	EFp2_init(&twisted_Q_36xxx);
	EFp2_init(&skew_Q);
	EFp2_init(&skew_Q_neg);
	EFp2_init(&skew_Q_puls1);
	EFp2_init(&minus_skew_Q_puls1);
	EFp2_init(&buf_Q);
	mpz_t A,B,s[4],buf;
	mpz_init(A);
	mpz_init(B);
	for(i=0; i<4; i++){
		mpz_init(s[i]);
	}
	mpz_init(buf);
	//table
	struct EFp2 table[15];
	for(i=0; i<15; i++){
		EFp2_init(&table[i]);
	}
	
	//gettimeofday(&t0,NULL);
	//twisted_Q
	EFp12_to_EFp2(&twisted_Q,Q);
	//twisted_Q_6xx
	EFp2_skew_frobenius_1(&skew_Q,&twisted_Q);
	EFp2_set_neg(&skew_Q_neg,&skew_Q);
	EFp2_set(&twisted_Q_6xx,&skew_Q);
	//twisted_Q_6x
	EFp2_ECA(&skew_Q_puls1,&skew_Q,&twisted_Q);
	EFp2_ECA(&minus_skew_Q_puls1,&skew_Q_neg,&twisted_Q);
	EFp2_skew_frobenius_3(&buf_Q,&minus_skew_Q_puls1);
	EFp2_ECA(&twisted_Q_6x,&skew_Q_puls1,&buf_Q);
	EFp2_set_neg(&twisted_Q_6x,&twisted_Q_6x);
	//twisted_Q_36xxx
	EFp2_skew_frobenius_1(&twisted_Q_36xxx,&twisted_Q_6x);
	
	//set table
	EFp2_set(&table[0],&twisted_Q);
	EFp2_set(&table[1],&twisted_Q_6x);
	EFp2_ECA(&table[2],&twisted_Q_6x,&twisted_Q);
	EFp2_set(&table[3],&twisted_Q_6xx);
	EFp2_ECA(&table[4],&twisted_Q_6xx,&twisted_Q);
	EFp2_ECA(&table[5],&twisted_Q_6xx,&twisted_Q_6x);
	EFp2_ECA(&table[6],&table[5],&twisted_Q);
	EFp2_set(&table[7],&twisted_Q_36xxx);
	EFp2_ECA(&table[8],&twisted_Q_36xxx,&twisted_Q);
	EFp2_ECA(&table[9],&twisted_Q_36xxx,&twisted_Q_6x);
	EFp2_ECA(&table[10],&twisted_Q_36xxx,&table[2]);
	EFp2_ECA(&table[11],&twisted_Q_36xxx,&twisted_Q_6xx);
	EFp2_ECA(&table[12],&table[11],&twisted_Q);
	EFp2_ECA(&table[13],&table[11],&twisted_Q_6x);
	EFp2_ECA(&table[14],&table[13],&twisted_Q);
	
	//set
	//s0,s1,s2,s3
	mpz_sub_ui(buf,trace_t,1);
	mpz_tdiv_qr(B,A,S,buf);
	mpz_mul_ui(buf,mother_parameter,6);
	mpz_tdiv_qr(s[1],s[0],A,buf);
	mpz_tdiv_qr(s[3],s[2],B,buf);
	
	//binary
	loop_length=0;
	for(i=0; i<4; i++){
		length_s[i]=(int)mpz_sizeinbase(s[i],2);
		//printf("G2 length_s%d:%d\n",i,length_s[i]);
		if(loop_length<length_s[i]){
			loop_length=length_s[i];
		}
	}
	//printf("\n");
	//set binary
	char binary_s[4][loop_length+1];
	char check_start[4],*e;
	int start;
	for(i=0; i<4; i++){
		if(length_s[i]==loop_length){
			mpz_get_str(binary_s[i],2,s[i]);
			check_start[3-i]='1';
		}else{
			char binary_buf[loop_length+1];
			mpz_get_str(binary_buf,2,s[i]);
			memset(binary_s[i],'0',sizeof(binary_s[i]));
			memmove(binary_s[i]+loop_length-length_s[i],binary_buf,sizeof(binary_buf));
			check_start[3-i]='0';
		}
		//printf("binary_s%d:%s\n",i,binary_s[i]);
	}
	//printf("\n");
	start=strtol(check_start,&e,2);
	EFp2_set(&next_twisted_Q,&table[start-1]);
	//gettimeofday(&t1,NULL);
	//printf("set time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	//gettimeofday(&t0,NULL);
	//SCM
	for(i=1; i<loop_length; i++){
		EFp2_ECD(&next_twisted_Q,&next_twisted_Q);
		if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[0]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[1]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[2]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[3]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[4]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[5]);
		}else if(binary_s[3][i]== '0' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[6]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[7]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[8]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[9]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '0' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[10]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[11]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '0' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[12]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '0'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[13]);
		}else if(binary_s[3][i]== '1' && binary_s[2][i] == '1' && binary_s[1][i] == '1' && binary_s[0][i] == '1'){
			EFp2_ECA(&next_twisted_Q,&next_twisted_Q,&table[14]);
		}
	}
	//gettimeofday(&t1,NULL);
	//printf("loop time:%.2f[ms]\n",timedifference_msec(t0,t1));
	
	EFp2_to_EFp12(ANS,&next_twisted_Q);
	ANS->flag=next_twisted_Q.flag;
	
	EFp12_clear(&Test);
	EFp2_clear(&next_twisted_Q);
	EFp2_clear(&twisted_Q);
	EFp2_clear(&twisted_Q_6x);
	EFp2_clear(&twisted_Q_6xx);
	EFp2_init(&twisted_Q_36xxx);
	EFp2_clear(&skew_Q);
	EFp2_clear(&skew_Q_neg);
	EFp2_clear(&skew_Q_puls1);
	EFp2_clear(&minus_skew_Q_puls1);
	EFp2_clear(&buf_Q);
	for(i=0; i<4; i++){
		mpz_clear(s[i]);
	}
	mpz_clear(buf);
	for(i=0; i<15; i++){
		EFp2_clear(&table[i]);
	}
}
/*-----------------------------frobenius--------------------------------*/
void EFp12_frobenius(struct EFp12 *ANS,struct EFp12 *P){
	Fp12_frobenius_1(&ANS->x,&P->x);
	Fp12_frobenius_1(&ANS->y,&P->y);
}
void EFp12_frobenius_2(struct EFp12 *ANS,struct EFp12 *P){
	Fp12_frobenius_2(&ANS->x,&P->x);
	Fp12_frobenius_2(&ANS->y,&P->y);
}
void EFp12_frobenius_3(struct EFp12 *ANS,struct EFp12 *P){
	Fp12_frobenius_3(&ANS->x,&P->x);
	Fp12_frobenius_3(&ANS->y,&P->y);
}
void EFp12_frobenius_10(struct EFp12 *ANS,struct EFp12 *P){
	Fp12_frobenius_10(&ANS->x,&P->x);
	Fp12_frobenius_10(&ANS->y,&P->y);
}
void EFp12_frobenius_G2optimal(struct EFp12 *ANS,struct EFp12 *P){
	EFp12_set_ui(ANS,0);
	Fp12_pow(&ANS->x,&P->x,prime);
	Fp12_pow(&ANS->y,&P->y,prime);
}

/*============================================================================*/
/* sextic twist                                                               */
/*============================================================================*/
void EFp12_to_EFp2(struct EFp2 *ANS,struct EFp12 *P){
	Fp2_set_ui(&ANS->x,0);
	Fp2_set(&ANS->x,&P->x.x1.x1);
	Fp2_mul_basis(&ANS->x,&ANS->x);
	Fp2_set_ui(&ANS->y,0);
	Fp2_set(&ANS->y,&P->y.x0.x1);
	Fp2_mul_basis(&ANS->y,&ANS->y);
	ANS->flag=P->flag;
}
void EFp2_to_EFp12(struct EFp12 *ANS,struct EFp2 *P){
	Fp12_set_ui(&ANS->x,0);
	Fp2_set(&ANS->x.x1.x1,&P->x);
	Fp2_inv_basis(&ANS->x.x1.x1,&ANS->x.x1.x1);
	Fp12_set_ui(&ANS->y,0);
	Fp2_set(&ANS->y.x0.x1,&P->y);
	Fp2_inv_basis(&ANS->y.x0.x1,&ANS->y.x0.x1);
	ANS->flag=P->flag;
}
void EFp2_to_EFp2(struct EFp2 *ANS,struct EFp2 *P){
	Fp2_inv_basis(&ANS->x,&P->x);
	Fp2_inv_basis(&ANS->y,&ANS->y);
}
/*============================================================================*/
/* final exp                                                                  */
/*============================================================================*/
//normal final exp
void EFp12_pairing_final_exp(struct Fp12 *ANS,struct Fp12 *A){
	//struct timeval t0,t1;
	struct Fp12 Tmp,Buf1,Buf2;
	Fp12_init(&Tmp);
	Fp12_set(&Tmp,A);
	Fp12_init(&Buf1);
	Fp12_init(&Buf2);
	mpz_t exp;
	mpz_init(exp);
	
	Fp2_set(&Buf1.x0.x0,&Tmp.x0.x0);
	Fp2_set_neg(&Buf1.x0.x1,&Tmp.x0.x1);
	Fp2_set_neg(&Buf1.x1.x0,&Tmp.x1.x0);
	Fp2_set(&Buf1.x1.x1,&Tmp.x1.x1);
	Fp2_set(&Buf1.x2.x0,&Tmp.x2.x0);
	Fp2_set_neg(&Buf1.x2.x1,&Tmp.x2.x1);
	Fp12_inv(&Buf2,&Tmp);
	Fp12_mul(&Tmp,&Buf1,&Buf2);
	
	Fp2_set(&Buf1.x0.x0,&Tmp.x0.x0);
	Fp2_set_neg(&Buf1.x0.x1,&Tmp.x0.x1);
	Fp2_mul_mpz(&Buf1.x1.x0,&Tmp.x1.x0,scalar1_of_prime_exp_2.x0.x0);
	Fp2_mul_mpz(&Buf1.x1.x1,&Tmp.x1.x1,scalar1_of_prime_exp_2.x0.x0);
	Fp2_set_neg(&Buf1.x1.x1,&Buf1.x1.x1);
	Fp2_mul_mpz(&Buf1.x2.x0,&Tmp.x2.x0,scalar2_of_prime_exp_2.x0.x0);
	Fp2_mul_mpz(&Buf1.x2.x1,&Tmp.x2.x1,scalar2_of_prime_exp_2.x0.x0);
	Fp2_set_neg(&Buf1.x2.x1,&Buf1.x2.x1);
	Fp12_mul(&Tmp,&Buf1,&Tmp);
	
	//gettimeofday(&t0,NULL);
	Fp12_pow(ANS,&Tmp,final_exp);
	//gettimeofday(&t1,NULL);
	//printf("final exp time ((p^4-p^2+1)/r):%.2f[ms]\n",timedifference_msec(t0,t1));
	
	mpz_clear(exp);
	Fp12_clear(&Tmp);
	Fp12_clear(&Buf1);
	Fp12_clear(&Buf2);
}
//which I found
void EFp12_pairing_final_exp_optimal1(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp12 Tmp,Buf1,Buf2,Buf3,a,b,c;
	Fp12_init(&Tmp);
	Fp12_set(&Tmp,A);
	Fp12_init(&Buf1);
	Fp12_init(&Buf2);
	Fp12_init(&Buf3);
	Fp12_init(&a);
	Fp12_init(&b);
	Fp12_init(&c);
	mpz_t exp;
	mpz_init(exp);
	//f←f^(p^6)*f^-1
	Fp12_frobenius_6(&Buf1,&Tmp);		//f^(p^6)
	Fp12_inv(&Buf2,&Tmp);			//f^-1
	Fp12_mul(&Tmp,&Buf1,&Buf2);		//f^(p^6)*f^-1
	
	//f←f^(p^2)*f
	Fp12_frobenius_2(&Buf1,&Tmp);		//f^(p^2)
	Fp12_mul(&Tmp,&Buf1,&Tmp);		//f^(p^2)*f
	//Fp12_pow(ANS,&Tmp,final_exp);
	
	//a←(f^(f^6))*(6x+5)
	Fp12_frobenius_6(&Buf1,&Tmp);//f^(p^6)
	mpz_mul_ui(exp,mother_parameter,6);
	mpz_add_ui(exp,exp,5);
	Fp12_pow(&a,&Buf1,exp);
	
	//b←a^p
	Fp12_pow(&b,&a,prime);
	//b←a*b
	Fp12_mul(&b,&a,&b);
	
	//compute f^p,f^p^2,f^p^3
	Fp12_frobenius_1(&Buf1,&Tmp);		//f^p
	Fp12_frobenius_2(&Buf2,&Tmp);		//f^p^2
	Fp12_frobenius_3(&Buf3,&Tmp);		//f^p^3
	
	Fp12_squaring(&c,&Buf1);		//b*(f^p)^2*f^p^2
	Fp12_mul(&c,&c,&b);
	Fp12_mul(&c,&c,&Buf2);
	
	Fp12_mul(&Buf1,&Buf1,&Tmp);		//f^p^3*(c^6)^x^2*c*b*(f^p*f)^9*a*f^4
	Fp12_squaring(&Buf2,&Buf1);		//(f^p*f)^9
	Fp12_squaring(&Buf2,&Buf2);
	Fp12_squaring(&Buf2,&Buf2);
	Fp12_mul(&Buf1,&Buf1,&Buf2);
	Fp12_mul(&Buf1,&Buf1,&a);
	Fp12_mul(&Buf1,&Buf1,&b);
	Fp12_mul(&Buf1,&Buf1,&c);		//c*b*(f^p*f)^9*a
	
	Fp12_squaring(&Buf2,&c);
	Fp12_squaring(&Buf2,&Buf2);
	Fp12_mul(&Buf2,&Buf2,&c);
	Fp12_mul(&c,&Buf2,&c);			//(c^6)
	mpz_mul(exp,mother_parameter,mother_parameter);
	Fp12_pow(&c,&c,exp);			//(c^6)^x^2
	Fp12_mul(&Buf1,&Buf1,&c);		//(c^6)^x^2*c*b*(f^p*f)^9*a
	
	Fp12_squaring(&Buf2,&Tmp);
	Fp12_squaring(&Buf2,&Buf2);		//f^4
	Fp12_mul(&Buf1,&Buf1,&Buf2);		//(c^6)^x^2*c*b*(f^p*f)^9*a*f^4
	
	Fp12_mul(ANS,&Buf1,&Buf3);		//f^p^3*(c^6)^x^2*c*b*(f^p*f)^9*a*f^4
	
	mpz_clear(exp);
	Fp12_clear(&a);
	Fp12_clear(&b);
	Fp12_clear(&c);
	Fp12_clear(&Tmp);
	Fp12_clear(&Buf1);
	Fp12_clear(&Buf2);
	Fp12_clear(&Buf3);
}
//On the Computation of the Optimal Ate Pairing at the 192-bit Security Level Loubna Ghammam and Emmanuel Fouotsa Algo.1
//cannot use
/*void EFp12_pairing_final_exp_optimal2(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp12 Tmp,t0,t1,t2,t3,t4,t5;
	Fp12_init(&Tmp);
	Fp12_init(&t0);
	Fp12_init(&t1);
	Fp12_init(&t2);
	Fp12_init(&t3);
	Fp12_init(&t4);
	Fp12_init(&t5);
	
	mpz_t a,b,c,d;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(d);
	
	mpz_pow_ui(d,mother_parameter,2);
	mpz_mul_ui(c,mother_parameter,2);
	mpz_sub(d,d,c);
	mpz_add_ui(d,d,1);
	
	mpz_mul(c,d,mother_parameter);
	
	mpz_mul(b,c,mother_parameter);
	mpz_sub(b,b,d);
	
	mpz_mul(a,b,mother_parameter);
	mpz_add_ui(a,a,3);
	
	Fp12_set(&Tmp,A);
	
	//f←f^(p^6)*f^-1
	Fp12_frobenius_6(&t0,&Tmp);//f^(p^6)
	Fp12_inv(&t1,&Tmp);//f^-1
	Fp12_mul(&Tmp,&t0,&t1);//f^(p^6)*f^-1
	
	//f←f^(p^2)*f
	Fp12_frobenius_2(&t0,&Tmp);//f^(p^2)
	Fp12_mul(&Tmp,&t0,&Tmp);//f^(p^2)*f
	
	Fp12_squaring(&t0,&Tmp);
	Fp12_frobenius_6(&t0,&t0);
	Fp12_pow(&t5,&Tmp,mother_parameter);
	Fp12_squaring(&t1,&t5);
	Fp12_mul(&t3,&t0,&t5);
	
	Fp12_pow(&t0,&t3,mother_parameter);
	Fp12_pow(&t2,&t0,mother_parameter);
	Fp12_pow(&t4,&t2,mother_parameter);
	
	Fp12_mul(&t4,&t1,&t4);
	Fp12_pow(&t1,&t4,mother_parameter);
	Fp12_frobenius_6(&t3,&t3);
	Fp12_mul(&t1,&t3,&t1);
	Fp12_mul(&t1,&t1,&Tmp);
	
	Fp12_frobenius_6(&t3,&Tmp);
	Fp12_mul(&t0,&t0,&Tmp);
	Fp12_frobenius_3(&t0,&t0);
	
	Fp12_mul(&t4,&t3,&t4);
	Fp12_frobenius_1(&t4,&t4);
	
	Fp12_mul(&t5,&t2,&t5);
	
	Fp12_frobenius_2(&t5,&t5);
	
	Fp12_mul(&t5,&t5,&t0);
	Fp12_mul(&t5,&t5,&t4);
	Fp12_mul(ANS,&t5,&t1);
	
	Fp12_clear(&Tmp);
	Fp12_clear(&t0);
	Fp12_clear(&t1);
	Fp12_clear(&t2);
	Fp12_clear(&t3);
	Fp12_clear(&t4);
	Fp12_clear(&t5);
}*/
//which alamin san gave
void EFp12_pairing_final_exp_optimal3(struct Fp12 *ANS,struct Fp12 *A){
	struct Fp12 Tmp,t0,t1,t2,t3,t4;
	Fp12_init(&Tmp);
	Fp12_init(&t0);
	Fp12_init(&t1);
	Fp12_init(&t2);
	Fp12_init(&t3);
	Fp12_init(&t4);
	
	Fp12_set(&Tmp,A);
	
	//f←f^(p^6)*f^-1
	Fp12_frobenius_6(&t0,&Tmp);//f^(p^6)
	Fp12_inv(&t1,&Tmp);//f^-1
	Fp12_mul(&Tmp,&t0,&t1);//f^(p^6)*f^-1
	
	//f←f^(p^2)*f
	Fp12_frobenius_2(&t0,&Tmp);//f^(p^2)
	Fp12_mul(&Tmp,&t0,&Tmp);//f^(p^2)*f
	
	Fp12_pow(&t0,&Tmp,mother_parameter);	//t0←f^(-u)
	Fp12_frobenius_6(&t0,&t0);
	Fp12_squaring(&t0,&t0);				//t0←t0^2
	Fp12_squaring(&t1,&t0);				//t1←t0^2
	Fp12_mul(&t1,&t0,&t1);				//t1←t0*t1
	Fp12_pow(&t2,&t1,mother_parameter);		//t2←t1^(-u)
	Fp12_frobenius_6(&t2,&t2);
	Fp12_frobenius_6(&t3,&t1);			//t3←t1^-1
	Fp12_mul(&t1,&t2,&t3);				//t1←t2*t3
	Fp12_squaring(&t3,&t2);				//t3←t2^2
	Fp12_pow(&t4,&t3,mother_parameter);		//t4←t3^(-u)
	Fp12_frobenius_6(&t4,&t4);
	Fp12_frobenius_6(&t4,&t4);			//t4←t4^(-1)
	Fp12_mul(&t4,&t4,&t1);				//t4←t4*t1
	Fp12_mul(&t3,&t4,&t0);				//t3←t4*t0
	Fp12_mul(&t0,&t2,&t4);				//t0←t2*t4
	Fp12_mul(&t0,&t0,&Tmp);				//t0←t0*f
	Fp12_frobenius_1(&t2,&t3);			//t2←t3^p
	Fp12_mul(&t0,&t2,&t0);				//t0←t2*t0
	Fp12_frobenius_2(&t2,&t4);			//t2←t4^(p^2)
	Fp12_mul(&t0,&t2,&t0);				//t0←t2*t0
	Fp12_frobenius_6(&t2,&Tmp);			//t2←f^(-1)
	Fp12_mul(&t2,&t2,&t3);				//t2←t2*t3
	Fp12_frobenius_3(&t2,&t2);			//t2←t2^(p^3)
	Fp12_mul(ANS,&t2,&t0);				//t0←t2*t0
	
	Fp12_clear(&Tmp);
	Fp12_clear(&t0);
	Fp12_clear(&t1);
	Fp12_clear(&t2);
	Fp12_clear(&t3);
	Fp12_clear(&t4);
}
//female_researcher's algo
void EFp12_pairing_final_exp_female_researcher(struct Fp12 *ANS,struct Fp12 *A){
	//Fp12_set_ui(A,0);
	//Fp_set_ui(&A->x0.x0.x0,1);
	struct Fp12 tmp,t0,t1,t2,t3;
	Fp12_init(&tmp);
	Fp12_init(&t0);
	Fp12_init(&t1);
	Fp12_init(&t2);
	Fp12_init(&t3);
	struct Fp2 test1;
	Fp2_init(&test1);
	mpz_t exp;
	mpz_init(exp);
	
	mpz_add_ui(exp,mother_parameter,1);
	
	
	//f←f^(p^6)*f^-1
	Fp12_frobenius_6(&t0,A);//f^(p^6)
	Fp12_inv(&t1,A);//f^-1
	Fp12_mul(&tmp,&t0,&t1);//f^(p^6)*f^-1
	
	//f←f^(p^2)*f
	Fp12_frobenius_2(&t0,&tmp);//f^(p^2)
	Fp12_mul(&tmp,&t0,&tmp);//f^(p^2)*f
	
	//Fp12_pow(ANS,&tmp,final_exp);
	//f←f^(d'(u))
	
	Fp12_pow(&t0,&tmp,mother_parameter);	//t0←f^(-u)
	//Fp12_inv(&t0,&t0);
	Fp12_frobenius_6(&t0,&t0);
	
	Fp12_squaring(&t1,&t0);				//t1←t0^2
	Fp12_squaring(&t0,&t1);				//t0←t1^2
	Fp12_mul(&t0,&t1,&t0);				//t0←t1*t0
	Fp12_pow(&t2,&t0,mother_parameter);		//t2←t0^(-u)
	//Fp12_inv(&t2,&t2);
	Fp12_frobenius_6(&t2,&t2);
	
	Fp12_pow(&t3,&t2,exp);				//t3←t2^(u+1)
	Fp12_squaring(&t3,&t3);				//t3←t3^2
	//Fp12_inv(&t0,&t0);				//t0←t0^(-1)
	Fp12_frobenius_6(&t0,&t0);
	Fp12_mul(&t3,&t3,&t0);				//t3←t3*t0
	//Fp12_inv(&t2,&t2);				//t2←t2^(-1)
	Fp12_frobenius_6(&t2,&t2);
	Fp12_mul(&t2,&t3,&t2);				//t2←t3*t2
	Fp12_mul(&t3,&t3,&tmp);				//t3←t3*f
	
	Fp12_mul(&t1,&t1,&t2);				//t1←t1*t2
	//Fp12_inv(&t0,&tmp);				//t0←f^(-1)
	Fp12_frobenius_6(&t0,&tmp);
	Fp12_mul(&t0,&t1,&t0);				//t0←t1*t0
	
	Fp12_frobenius_3(&t0,&t0);			//t0←t0^(p^3)
	Fp12_mul(&t0,&t0,&t3);				//t0←t0*t3
	Fp12_frobenius_1(&t1,&t1);			//t1←t1^p
	Fp12_mul(&t0,&t0,&t1);				//t0←t0*t1
	Fp12_frobenius_2(&t2,&t2);			//t2←t2^(p^2)
	Fp12_mul(&t0,&t0,&t2);				//t0←t0*t2
	
	Fp12_set(ANS,&t0);
	
	Fp12_clear(&tmp);
	Fp12_clear(&t0);
	Fp12_clear(&t1);
	Fp12_clear(&t2);
	Fp12_clear(&t3);
	mpz_clear(exp);
}
/*============================================================================*/
/* ltt,ltq                                                                    */
/*============================================================================*/
void ff_ltt_for_ate(struct Fp12 *f,struct EFp2 *T,struct EFp *P){
	struct Fp12 Test;
	Fp12_init(&Test);
	struct EFp2 tmp_T;
	EFp2_init(&tmp_T);
	EFp2_set(&tmp_T,T);
	struct Fp2 A,B,C,D,E;
	Fp2_init(&A);
	Fp2_init(&B);
	Fp2_init(&C);
	Fp2_init(&D);
	Fp2_init(&E);
	
	Fp2_add(&A,&tmp_T.y,&tmp_T.y);//A=2y^(-1)
	Fp2_inv(&A,&A);
	Fp2_squaring(&B,&tmp_T.x);	//B=3x^2
	Fp2_mul_ui(&B,&B,3);
	Fp2_mul(&C,&A,&B);		//C=A*B
	Fp2_add(&D,&tmp_T.x,&tmp_T.x);//D=2x
	Fp2_squaring(&T->x,&C);		//C^2-D
	Fp2_sub(&T->x,&T->x,&D);
	
	Fp2_mul(&E,&C,&tmp_T.x);	//E=Cx-y
	Fp2_sub(&E,&E,&tmp_T.y);
	Fp2_mul(&T->y,&C,&T->x);	//y3=E-Cx3
	Fp2_sub(&T->y,&E,&T->y);
	
	Fp_set(&Test.x0.x0.x0,&P->y);
	Fp2_set(&Test.x0.x1,&E);
	Fp2_inv_basis(&Test.x0.x1,&Test.x0.x1);
	Fp2_mul_mpz(&Test.x2.x1,&C,P->x.x0);
	Fp2_set_neg(&Test.x2.x1,&Test.x2.x1);
	Fp2_inv_basis(&Test.x2.x1,&Test.x2.x1);
	
	Fp12_squaring(f,f);
	Fp12_mul_101100000011_111111111111(f,&Test,f);
	//Fp12_mul(f,&Test,f);
	
	//EFp2_set(T,&tmp_T);
	
	Fp2_clear(&A);
	Fp2_clear(&B);
	Fp2_clear(&C);
	Fp2_clear(&D);
	Fp2_clear(&E);
	EFp2_clear(&tmp_T);
	Fp12_clear(&Test);
}
void f_ltq_for_ate(struct Fp12 *f,struct EFp2 *T,struct EFp2 *Q,struct EFp *P){
	struct Fp12 Test;
	Fp12_init(&Test);
	struct EFp2 tmp_T;
	EFp2_init(&tmp_T);
	EFp2_set(&tmp_T,T);
	struct Fp2 A,B,C,D,E;
	Fp2_init(&A);
	Fp2_init(&B);
	Fp2_init(&C);
	Fp2_init(&D);
	Fp2_init(&E);
	
	Fp2_sub(&A,&Q->x,&tmp_T.x);//A=Q.x-T.x
	Fp2_inv(&A,&A);
	Fp2_sub(&B,&Q->y,&tmp_T.y);	//B=Q.y-T.y
	Fp2_mul(&C,&A,&B);		//C=A*B
	Fp2_add(&D,&Q->x,&tmp_T.x);//D=Q.x+T.x
	Fp2_squaring(&T->x,&C);		//C^2-D
	Fp2_sub(&T->x,&T->x,&D);
	
	Fp2_mul(&E,&C,&tmp_T.x);	//E=Cx-y
	Fp2_sub(&E,&E,&tmp_T.y);
	Fp2_mul(&T->y,&C,&T->x);	//y3=E-Cx3
	Fp2_sub(&T->y,&E,&T->y);
	
	Fp_set(&Test.x0.x0.x0,&P->y);
	Fp2_set(&Test.x0.x1,&E);
	Fp2_inv_basis(&Test.x0.x1,&Test.x0.x1);
	Fp2_mul_mpz(&Test.x2.x1,&C,P->x.x0);
	Fp2_set_neg(&Test.x2.x1,&Test.x2.x1);
	Fp2_inv_basis(&Test.x2.x1,&Test.x2.x1);
	
	Fp12_mul_101100000011_111111111111(f,&Test,f);
	//Fp12_mul(f,&Test,f);
	
	//EFp2_set(T,&tmp_T);
	
	Fp2_clear(&A);
	Fp2_clear(&B);
	Fp2_clear(&C);
	Fp2_clear(&D);
	Fp2_clear(&E);
	EFp2_clear(&tmp_T);
	Fp12_clear(&Test);
}
/*============================================================================*/
/* Opt-ate                                                                    */
/*============================================================================*/
void miller_for_opt_ate(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P){
	struct EFp12 Buf;
	EFp12_init(&Buf);
	struct EFp2 T;
	EFp2_init(&T);
	struct EFp2 twisted_Q,twisted_Q_neg,twisted_Q1,twisted_Q2_neg;
	EFp2_init(&twisted_Q);
	EFp2_init(&twisted_Q_neg);
	EFp2_init(&twisted_Q1);
	EFp2_init(&twisted_Q2_neg);
	struct EFp tmp_P;
	EFp_init(&tmp_P);
	struct Fp12 f;
	Fp12_init(&f);
	int i;
	
	//set
	EFp12_to_EFp2(&twisted_Q,Q);//set twisted_Q
	EFp2_set(&twisted_Q_neg,&twisted_Q);//set twisted_Q_neg
	Fp2_set_neg(&twisted_Q_neg.y,&twisted_Q_neg.y);
	Fp_set(&tmp_P.x,&P->x.x0.x0.x0);	//set P
	Fp_set(&tmp_P.y,&P->y.x0.x0.x0);
	tmp_P.flag=P->flag;
	EFp2_set(&T,&twisted_Q);		//set T
	Fp12_set_ui(&f,0);			//set f
	Fp_set_ui(&f.x0.x0.x0,1);
	//miller
	for(i=x_bit_for_opt_ate-1; i>=0; i--){
		switch(X_bit_binary_for_opt_ate[i]){
			case 0:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				break;
			case 1:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				f_ltq_for_ate(&f,&T,&twisted_Q,&tmp_P);
				break;
			case -1:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				f_ltq_for_ate(&f,&T,&twisted_Q_neg,&tmp_P);
				break;
			default:
				break;
		}
		
	}
	
	EFp2_skew_frobenius_1(&twisted_Q1,&twisted_Q);//Q^p
	EFp2_skew_frobenius_2(&twisted_Q2_neg,&twisted_Q);//Q^(p^2)
	EFp2_set_neg(&twisted_Q2_neg,&twisted_Q2_neg);
	f_ltq_for_ate(&f,&T,&twisted_Q1,&tmp_P);
	f_ltq_for_ate(&f,&T,&twisted_Q2_neg,&tmp_P);
	
	Fp12_set(ANS,&f);
	
	EFp12_clear(&Buf);
	Fp12_clear(&f);
	EFp2_clear(&T);
	EFp2_clear(&twisted_Q);
	EFp2_clear(&twisted_Q_neg);
	EFp2_clear(&twisted_Q1);
	EFp2_clear(&twisted_Q2_neg);
	EFp_clear(&tmp_P);
}
void Opt_ate_pairing(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P){
	struct timeval t0,t1;
	gettimeofday(&t0,NULL);
	miller_for_opt_ate(ANS,Q,P);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", timedifference_msec(t0,t1));
	gettimeofday(&t0,NULL);
	EFp12_pairing_final_exp_optimal3(ANS,ANS);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", timedifference_msec(t0,t1));
}
void Opt_ate_pairing_return_time(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P,float *total,float *miller,float *finalexp1,float *finalexp3,float *normal_finalexp){
	struct timeval t0,t1,total0,total1;
	printf("opt-ate pairing\n");
	//optimal3 finalexp
	gettimeofday(&total0,NULL);
	gettimeofday(&t0,NULL);
	miller_for_opt_ate(ANS,Q,P);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", *miller=timedifference_msec(t0,t1));
	gettimeofday(&t0,NULL);
	EFp12_pairing_final_exp_optimal3(ANS,ANS);
	gettimeofday(&t1,NULL);
	printf("optimal final exp:%.2f[ms]\n", *finalexp3=timedifference_msec(t0,t1));
	gettimeofday(&total1,NULL);
	printf("total time:%.2f[ms]\n\n", *total=timedifference_msec(total0,total1));
	
	printf("another final exp\n");
	//optimal1 finalexp
	gettimeofday(&total0,NULL);
	gettimeofday(&t0,NULL);
	miller_for_opt_ate(ANS,Q,P);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", timedifference_msec(t0,t1));
	gettimeofday(&t0,NULL);
	EFp12_pairing_final_exp_optimal1(ANS,ANS);
	gettimeofday(&t1,NULL);
	printf("another optimal final exp:%.2f[ms]\n", *finalexp1=timedifference_msec(t0,t1));
	gettimeofday(&total1,NULL);
	printf("total time:%.2f[ms]\n\n", timedifference_msec(total0,total1));
	
	printf("normal final exp\n");
	//optimal1 finalexp
	gettimeofday(&total0,NULL);
	gettimeofday(&t0,NULL);
	miller_for_opt_ate(ANS,Q,P);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", timedifference_msec(t0,t1));
	gettimeofday(&t0,NULL);
	EFp12_pairing_final_exp(ANS,ANS);
	gettimeofday(&t1,NULL);
	printf("normal final exp:%.2f[ms]\n", *normal_finalexp=timedifference_msec(t0,t1));
	gettimeofday(&total1,NULL);
	printf("total time:%.2f[ms]\n\n", timedifference_msec(total0,total1));
}
/*============================================================================*/
/* X-ate                                                                      */
/*============================================================================*/
void miller_for_x_ate(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P){
	struct timeval t0,t1;
	struct EFp12 Buf;
	EFp12_init(&Buf);
	struct EFp2 T;
	EFp2_init(&T);
	struct EFp2 twisted_Q,twisted_Q_neg,twisted_Q1,twisted_Q2;
	EFp2_init(&twisted_Q);
	EFp2_init(&twisted_Q_neg);
	EFp2_init(&twisted_Q1);
	EFp2_init(&twisted_Q2);
	struct EFp tmp_P;
	EFp_init(&tmp_P);
	struct Fp12 f;
	Fp12_init(&f);
	int i;
	
	gettimeofday(&t0,NULL);
	//set
	EFp12_to_EFp2(&twisted_Q,Q);//set twisted_Q
	EFp2_set(&twisted_Q_neg,&twisted_Q);//set twisted_Q_neg
	Fp2_set_neg(&twisted_Q_neg.y,&twisted_Q_neg.y);
	Fp_set(&tmp_P.x,&P->x.x0.x0.x0);	//set P
	Fp_set(&tmp_P.y,&P->y.x0.x0.x0);
	tmp_P.flag=P->flag;
	EFp2_set(&T,&twisted_Q);		//set T
	Fp12_set_ui(&f,0);			//set f
	Fp_set_ui(&f.x0.x0.x0,1);	
	//miller
	for(i=x_bit-1; i>=0; i--){
		switch(X_bit_binary[i]){
			case 0:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				break;
			case 1:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				f_ltq_for_ate(&f,&T,&twisted_Q,&tmp_P);
				break;
			case -1:
				ff_ltt_for_ate(&f,&T,&tmp_P);
				f_ltq_for_ate(&f,&T,&twisted_Q_neg,&tmp_P);
				break;
			default:
				break;
		}
	}
		
	Fp12_frobenius_3(&Buf.x,&f);		//f←f*f^(p^3)
	Fp12_mul(&f,&Buf.x,&f);
	EFp2_skew_frobenius_3(&twisted_Q1,&T);//twisted_Q1←T^(p^3)
	EFp2_set(&twisted_Q2,&T);
	f_ltq_for_ate(&f,&twisted_Q2,&twisted_Q1,&tmp_P);
	Fp12_frobenius_10(&Buf.x,&f);		//f←f*f^(p^10)
	Fp12_mul(&f,&Buf.x,&f);
	EFp2_skew_frobenius_10(&T,&twisted_Q2);//T←Q2^(p^10)
	f_ltq_for_ate(&f,&T,&twisted_Q2,&tmp_P);
	
	Fp12_set(ANS,&f);
	
	
	EFp12_clear(&Buf);
	Fp12_clear(&f);
	EFp2_clear(&T);
	EFp2_clear(&twisted_Q);
	EFp2_clear(&twisted_Q_neg);
	EFp2_clear(&twisted_Q1);
	EFp2_clear(&twisted_Q2);
	EFp_clear(&tmp_P);
}
void X_ate_pairing(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P){
	struct timeval t0,t1;
	gettimeofday(&t0,NULL);
	miller_for_opt_ate(ANS,Q,P);
	gettimeofday(&t1,NULL);
	printf("miller loop:%.2f[ms]\n", timedifference_msec(t0,t1));
	EFp12_pairing_final_exp_female_researcher(ANS,ANS);
}
/*============================================================================*/
/*  init                                                                      */
/*============================================================================*/
void init_parameters(){
	//init
	mpz_init(prime);
	mpz_init(mother_parameter);
	mpz_init(trace_t);
	mpz_init(EFp_order);
	mpz_init(EFp_total);
	mpz_init(EFp2_total);
	mpz_init(EFp4_total);
	mpz_init(EFp12_total);
	mpz_init(curve_parameter_A);
	mpz_init(curve_parameter_B);
	mpz_init(final_exp);
	Fp_init(&Fp_basis);
	Fp2_init(&Fp2_basis_inv);
	Fp2_init(&Fp2_basis);
	Fp4_init(&Fp4_basis);
	Fp_init(&Fp_ZERO);
	Fp2_init(&Fp2_ZERO);
	Fp4_init(&Fp4_ZERO);
	Fp12_init(&Fp12_ZERO);
	Fp12_init(&Fp12_ONE);
	Fp_init(&inv_CNR1);
	Fp_init(&inv_CNR2);
	Fp_init(&epsilon_1);
	Fp_init(&epsilon_2);
	Fp2_init(&scalar1_of_prime_exp_1);
	Fp2_init(&scalar2_of_prime_exp_1);
	Fp2_init(&scalar3_of_prime_exp_1);
	Fp2_init(&scalar1_of_prime_exp_2);
	Fp2_init(&scalar2_of_prime_exp_2);
	Fp2_init(&scalar1_of_prime_exp_3);
	Fp2_init(&scalar2_of_prime_exp_3);
	Fp2_init(&scalar1_of_prime_exp_4);
	Fp2_init(&scalar2_of_prime_exp_4);
	Fp2_init(&scalar1_of_prime_exp_8);
	Fp2_init(&scalar2_of_prime_exp_8);
	Fp2_init(&scalar1_of_prime_exp_10);
	Fp2_init(&scalar2_of_prime_exp_10);
	Fp2_init(&x_of_skew_frobenius_1);
	Fp2_init(&y_of_skew_frobenius_1);
	Fp2_init(&x_of_skew_frobenius_2);
	Fp2_init(&y_of_skew_frobenius_2);
	Fp2_init(&x_of_skew_frobenius_3);
	Fp2_init(&y_of_skew_frobenius_3);
	Fp2_init(&x_of_skew_frobenius_10);
	Fp2_init(&y_of_skew_frobenius_10);
	memset(X_bit_binary,0,sizeof(X_bit_binary));
	memset(X_bit_binary_for_opt_ate,0,sizeof(X_bit_binary_for_opt_ate));
	//set ZERO
	Fp_set_ui(&Fp_ZERO,0);
	Fp2_set_ui(&Fp2_ZERO,0);
	Fp4_set_ui(&Fp4_ZERO,0);
	Fp12_set_ui(&Fp12_ZERO,0);
	//set
	Fp12_set_ui(&Fp12_ONE,0);
	Fp_set_ui(&Fp12_ONE.x0.x0.x0,1);
}

/*============================================================================*/
/*  set                                                                       */
/*============================================================================*/
void set_parameters(){
	mpz_t result;
	mpz_init(result);
	
	//set curve parameter
	mpz_set_ui(curve_parameter_A,0);
	mpz_set_ui(curve_parameter_B,4);
	
	//generate mother_parameter
	generate_mother_parameter();	
	sign=1;				//sign of mother_parameter
	
	//generate prime,order,trace
	if(generate_prime()==1 && generate_order()==1){
		generate_trace();
	}else{
		printf("This mother parameter cannot use.\n");
		clear_parameters();
		exit(1);
	}
	
	weil();				//total rational point
	get_epsilon();			//calculate 1^(1/3)
	generate_basis();			//set basis
	get_scalar_of_final_exp();	//get value
	
	mpz_clear(result);
}
void generate_mother_parameter(){
	int i;
	mpz_t buf,set_2;
	mpz_init(buf);
	mpz_init(set_2);
	mpz_set_ui(set_2,2);
	
	//X_bit_binary
	X_bit_binary[114]=1;
	X_bit_binary[101]=1;
	X_bit_binary[14]=-1;
	X_bit_binary[0]=-1;
	//X_bit_binary_for_opt_ate
	X_bit_binary_for_opt_ate[116]=1;
	X_bit_binary_for_opt_ate[115]=1;
	X_bit_binary_for_opt_ate[103]=1;
	X_bit_binary_for_opt_ate[102]=1;
	X_bit_binary_for_opt_ate[16]=-1;
	X_bit_binary_for_opt_ate[15]=-1;
	X_bit_binary_for_opt_ate[2]=-1;
	
	//mother_parameter
	mpz_set_ui(mother_parameter,0);
	for(i=x_bit; i>=0; i--){
		if(X_bit_binary[i]==1){
			mpz_pow_ui(buf,set_2,i);
			mpz_add(mother_parameter,mother_parameter,buf);
		}else if(X_bit_binary[i]==-1){
			mpz_pow_ui(buf,set_2,i);
			mpz_sub(mother_parameter,mother_parameter,buf);
		}
	}
	
	mpz_clear(buf);
	mpz_clear(set_2);
}
int generate_prime(){
	mpz_t buf1,buf2,base;
	mpz_init(buf1);
	mpz_init(buf2);
	mpz_init(base);
	mpz_set(base,mother_parameter);
	
	//prime
	mpz_pow_ui(buf1,base,4);
	mpz_mul_ui(buf1,buf1,36);
	mpz_set(buf2,buf1);
	mpz_pow_ui(buf1,base,3);
	mpz_mul_ui(buf1,buf1,36);
	if(sign==1){
		mpz_add(buf2,buf2,buf1);
	}else{
		mpz_sub(buf2,buf2,buf1);
	}
	mpz_pow_ui(buf1,base,2);
	mpz_mul_ui(buf1,buf1,24);
	mpz_add(buf2,buf2,buf1);
	mpz_mul_ui(buf1,base,6);
	if(sign==1){
		mpz_add(buf2,buf2,buf1);
	}else{
		mpz_sub(buf2,buf2,buf1);
	}
	mpz_add_ui(buf2,buf2,1);
	
	//isprime
	if(mpz_probab_prime_p(buf2,25)==0){
		mpz_clear(buf1);
		mpz_clear(buf2);
		mpz_clear(base);
		return 0;
	}else{
		mpz_set(prime,buf2);
		mpz_clear(buf1);
		mpz_clear(buf2);
		mpz_clear(base);
		return 1;
	}
}
int generate_order(){
	mpz_t buf1,buf2,base;
	mpz_init(buf1);
	mpz_init(buf2);
	mpz_init(base);
	mpz_set(base,mother_parameter);
	
	//order
	mpz_pow_ui(buf1,base,4);
	mpz_mul_ui(buf1,buf1,36);
	mpz_set(buf2,buf1);
	mpz_pow_ui(buf1,base,3);
	mpz_mul_ui(buf1,buf1,36);
	if(sign==1){
		mpz_add(buf2,buf2,buf1);
	}else{
		mpz_sub(buf2,buf2,buf1);
	}
	mpz_pow_ui(buf1,base,2);
	mpz_mul_ui(buf1,buf1,18);
	mpz_add(buf2,buf2,buf1);
	mpz_mul_ui(buf1,base,6);
	if(sign==1){
		mpz_add(buf2,buf2,buf1);
	}else{
		mpz_sub(buf2,buf2,buf1);
	}
	mpz_add_ui(buf2,buf2,1);
	
	//isprime
	if(mpz_probab_prime_p(buf2,25)==0){
		mpz_clear(buf1);
		mpz_clear(buf2);
		mpz_clear(base);
		return 0;
	}else{
		mpz_set(EFp_order,buf2);
		mpz_clear(buf1);
		mpz_clear(buf2);
		mpz_clear(base);
		return 1;
	}
}
void generate_trace(){
	mpz_t buf,base;
	mpz_init(buf);
	mpz_init(base);
	
	mpz_set(base,mother_parameter);
	mpz_pow_ui(buf,base,2);
	mpz_mul_ui(buf,buf,6);
	mpz_add_ui(trace_t,buf,1);
	
	mpz_clear(buf);
	mpz_clear(base);
}
void generate_basis(){
	unsigned long int i;
	
	//Fp_basis
	i=0;
	while(mpz_cmp_ui(prime,i)>0){
		Fp_set_ui(&Fp_basis,i);
		if(Fp_legendre(&Fp_basis)==1){
			break;
		}
		i++;
	}
	
	//Fp2_basis
	Fp2_set_ui(&Fp2_basis,0);
	Fp_set_ui(&Fp2_basis.x1,1);
	i=0;
	while(mpz_cmp_ui(prime,i)>0){
		Fp_set_ui(&Fp2_basis.x0,i);
		if(Fp2_legendre(&Fp2_basis)==-1){
			break;
		}
		i++;
	}
	//Fp2_basis_inv
	Fp2_inv(&Fp2_basis_inv,&Fp2_basis);
	
	//Fp12_basis
	Fp4_set_ui(&Fp4_basis,0);
	Fp_set_ui(&Fp4_basis.x1.x0,1);
	i=0;
	while(mpz_cmp_ui(prime,i)>0){
		Fp_set_ui(&Fp4_basis.x0.x0,i);
		if(Fp4_legendre(&Fp4_basis)==-1){
			break;
		}
		i++;
	}

}
void get_epsilon(){
	struct Fp inv,root,buf;
	Fp_init(&inv);
	Fp_init(&root);
	Fp_init(&buf);
	mpz_t exp;
	mpz_init(exp);
	
	Fp_set_ui(&buf,2);
	//Fp_inv(&inv,&buf);
	mpz_invert(inv.x0,buf.x0,prime);
	mpz_sub_ui(buf.x0,prime,3);
	Fp_sqrt(&root,&buf);
	Fp_sub_ui(&buf,&root,1);
	Fp_mul(&inv_CNR1,&buf,&inv);
	Fp_mul(&inv_CNR2,&inv_CNR1,&inv_CNR1);
	
	mpz_clear(exp);
	Fp_clear(&inv);
	Fp_clear(&root);
	Fp_clear(&buf);
}
void get_scalar_of_final_exp(){
	struct Fp2 Buf;
	Fp2_init(&Buf);
	
	mpz_t exp,buf;
	mpz_init(exp);
	mpz_init(buf);
	
	//skew_frobenius_1
	mpz_sub_ui(exp,prime,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&x_of_skew_frobenius_1,&Fp2_basis,exp);
	Fp2_inv(&x_of_skew_frobenius_1,&x_of_skew_frobenius_1);
	
	mpz_sub_ui(exp,prime,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&y_of_skew_frobenius_1,&Fp2_basis,exp);
	Fp2_inv(&y_of_skew_frobenius_1,&y_of_skew_frobenius_1);
	
	//skew_frobenius_2
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&x_of_skew_frobenius_2,&Fp2_basis,exp);
	Fp2_inv(&x_of_skew_frobenius_2,&x_of_skew_frobenius_2);
	
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&y_of_skew_frobenius_2,&Fp2_basis,exp);
	Fp2_inv(&y_of_skew_frobenius_2,&y_of_skew_frobenius_2);
	
	//skew_frobenius_3
	mpz_pow_ui(exp,prime,3);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&x_of_skew_frobenius_3,&Fp2_basis,exp);
	Fp2_inv(&x_of_skew_frobenius_3,&x_of_skew_frobenius_3);
	
	mpz_pow_ui(exp,prime,3);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&y_of_skew_frobenius_3,&Fp2_basis,exp);
	Fp2_inv(&y_of_skew_frobenius_3,&y_of_skew_frobenius_3);
	
	//skew_frobenius_10
	mpz_pow_ui(exp,prime,10);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&x_of_skew_frobenius_10,&Fp2_basis,exp);
	Fp2_inv(&x_of_skew_frobenius_10,&x_of_skew_frobenius_10);
	
	mpz_pow_ui(exp,prime,10);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&y_of_skew_frobenius_10,&Fp2_basis,exp);
	Fp2_inv(&y_of_skew_frobenius_10,&y_of_skew_frobenius_10);
	
	//scalar_prime_exp_1
	mpz_sub_ui(exp,prime,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&scalar1_of_prime_exp_1,&Fp2_basis,exp);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&scalar2_of_prime_exp_1,&Fp2_basis,exp);
	Fp2_mul(&scalar3_of_prime_exp_1,&scalar2_of_prime_exp_1,&scalar2_of_prime_exp_1);
	
	//scalar_prime_exp_2
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,6);
	Fp2_pow(&scalar1_of_prime_exp_2,&Fp2_basis,exp);
	Fp2_mul(&scalar2_of_prime_exp_2,&scalar1_of_prime_exp_2,&scalar1_of_prime_exp_2);
	
	//scalar_prime_exp_3
	mpz_pow_ui(exp,prime,3);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,2);
	Fp2_pow(&scalar1_of_prime_exp_3,&Fp2_basis,exp);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&scalar2_of_prime_exp_3,&Fp2_basis,exp);
	
	//scalar_prime_exp_4
	mpz_pow_ui(exp,prime,4);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,6);
	Fp2_pow(&scalar1_of_prime_exp_4,&Fp2_basis,exp);
	Fp2_mul(&scalar2_of_prime_exp_4,&scalar1_of_prime_exp_4,&scalar1_of_prime_exp_4);
	
	//scalar_prime_exp_8
	mpz_pow_ui(exp,prime,8);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,6);
	Fp2_pow(&scalar1_of_prime_exp_8,&Fp2_basis,exp);
	Fp2_mul(&scalar2_of_prime_exp_8,&scalar1_of_prime_exp_8,&scalar1_of_prime_exp_8);
	
	//scalar_prime_exp_10
	mpz_pow_ui(exp,prime,10);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,6);
	Fp2_pow(&scalar1_of_prime_exp_10,&Fp2_basis,exp);
	Fp2_mul(&scalar2_of_prime_exp_10,&scalar1_of_prime_exp_10,&scalar1_of_prime_exp_10);
	
	//final exp
	mpz_pow_ui(exp,prime,4);
	mpz_pow_ui(buf,prime,2);
	mpz_sub(exp,exp,buf);
	mpz_add_ui(exp,exp,1);
	mpz_tdiv_q(final_exp,exp,EFp_order);
	
	//epsilon
	mpz_pow_ui(exp,prime,2);
	mpz_sub_ui(exp,exp,1);
	mpz_tdiv_q_ui(exp,exp,3);
	Fp2_pow(&Buf,&Fp2_basis,exp);
	Fp_set(&epsilon_1,&Buf.x0);
	Fp2_mul(&Buf,&Buf,&Buf);
	Fp_set(&epsilon_2,&Buf.x0);
	
	mpz_clear(exp);
	mpz_clear(buf);
	Fp2_clear(&Buf);
}
void weil(){
	mpz_t t2,t4,t12,p_exp_2,p_exp_4,buf;
	mpz_init(t2);
	mpz_init(t4);
	mpz_init(t12);
	mpz_init(p_exp_2);
	mpz_init(p_exp_4);
	mpz_init(buf);
	
	//EFp_total
	mpz_add_ui(buf,prime,1);
	mpz_sub(EFp_total,buf,trace_t);
	
	//t2←α^2+β^2
	mpz_pow_ui(t2,trace_t,2);
	mpz_mul_ui(buf,prime,2);
	mpz_sub(t2,t2,buf);
	//EFp2_total
	mpz_pow_ui(p_exp_2,prime,2);
	mpz_sub(buf,p_exp_2,t2);
	mpz_add_ui(EFp2_total,buf,1);
	
	//α^4+β^4
	mpz_pow_ui(t4,t2,2);
	mpz_sub(t4,t4,p_exp_2);
	mpz_sub(t4,t4,p_exp_2);
	//EFp4_total
	mpz_pow_ui(p_exp_4,p_exp_2,2);
	mpz_sub(buf,p_exp_4,t4);
	mpz_add_ui(EFp4_total,buf,1);
	
	//α^12+β^12
	mpz_pow_ui(t12,t4,3);
	mpz_mul(buf,p_exp_4,t4);
	mpz_sub(t12,t12,buf);
	mpz_sub(t12,t12,buf);
	mpz_sub(t12,t12,buf);
	//EFp12_total
	mpz_pow_ui(buf,p_exp_4,3);
	mpz_sub(buf,buf,t12);
	mpz_add_ui(EFp12_total,buf,1);
	
	mpz_clear(t2);
	mpz_clear(t4);
	mpz_clear(t12);
	mpz_clear(p_exp_2);
	mpz_clear(p_exp_4);
	mpz_clear(buf);
}

/*============================================================================*/
/*  print                                                                     */
/*============================================================================*/
void print_parameters(){
	printf("====================================================================================\n");
	printf("prime length:%dbit\n",(int)mpz_sizeinbase(prime,2));
	printf("E:y^2=x^3-");
	if(mpz_cmp_ui(curve_parameter_A,0)!=0){
		mpz_out_str(stdout,10,curve_parameter_A);
		printf("x+");
	}
	if(mpz_cmp_ui(curve_parameter_B,0)!=0){
		mpz_out_str(stdout,10,curve_parameter_B);
	}
	printf("(mod");
	mpz_out_str(stdout,10,prime);
	printf(")\n");
	printf("mother parameter:");
	mpz_out_str(stdout,10,mother_parameter);
	printf("\n");
	printf("Fp2:f(x)=x^2+");
	Fp_printf(&Fp_basis,"");
	printf("\n");
	printf("Fp4:f(x)=x^2-");
	Fp2_printf(&Fp2_basis,"");
	printf("\n");
	printf("Fp12:f(x)=x^3-");
	Fp4_printf(&Fp4_basis,"");
	printf("\n");
	
	printf("EFp_order:");
	mpz_out_str(stdout,10,EFp_order);
	printf("\n");
	printf("trace_t=");
	mpz_out_str(stdout,10,trace_t);
	printf("\n");
}

/*============================================================================*/
/*  clear                                                                     */
/*============================================================================*/
void clear_parameters(){
	//clear
	mpz_clear(prime);
	mpz_clear(mother_parameter);
	mpz_clear(trace_t);
	mpz_clear(EFp_order);
	mpz_clear(EFp_total);
	mpz_clear(EFp2_total);
	mpz_clear(EFp4_total);
	mpz_clear(EFp12_total);
	mpz_clear(curve_parameter_A);
	mpz_clear(curve_parameter_B);
	mpz_clear(final_exp);
	Fp_clear(&Fp_basis);
	Fp2_clear(&Fp2_basis_inv);
	Fp2_clear(&Fp2_basis);
	Fp4_clear(&Fp4_basis);
	Fp_clear(&Fp_ZERO);
	Fp2_clear(&Fp2_ZERO);
	Fp4_clear(&Fp4_ZERO);
	Fp12_clear(&Fp12_ZERO);
	Fp12_clear(&Fp12_ONE);
	Fp_clear(&inv_CNR1);
	Fp_clear(&inv_CNR2);
	Fp_clear(&epsilon_1);
	Fp_clear(&epsilon_2);
	Fp2_clear(&scalar1_of_prime_exp_1);
	Fp2_clear(&scalar2_of_prime_exp_1);
	Fp2_clear(&scalar3_of_prime_exp_1);
	Fp2_clear(&scalar1_of_prime_exp_2);
	Fp2_clear(&scalar2_of_prime_exp_2);
	Fp2_clear(&scalar1_of_prime_exp_3);
	Fp2_clear(&scalar2_of_prime_exp_3);
	Fp2_clear(&scalar1_of_prime_exp_4);
	Fp2_clear(&scalar2_of_prime_exp_4);
	Fp2_clear(&scalar1_of_prime_exp_8);
	Fp2_clear(&scalar2_of_prime_exp_8);
	Fp2_clear(&scalar1_of_prime_exp_10);
	Fp2_clear(&scalar2_of_prime_exp_10);
	Fp2_clear(&x_of_skew_frobenius_1);
	Fp2_clear(&y_of_skew_frobenius_1);
	Fp2_clear(&x_of_skew_frobenius_2);
	Fp2_clear(&y_of_skew_frobenius_2);
	Fp2_clear(&x_of_skew_frobenius_3);
	Fp2_clear(&y_of_skew_frobenius_3);
	Fp2_clear(&x_of_skew_frobenius_10);
	Fp2_clear(&y_of_skew_frobenius_10);
}
/*============================================================================*/
/* test for RaspberryPi                                                       */
/*============================================================================*/
void test_for_RaspberryPi(){
	printf("====================================================================================\n");
	struct timeval t0,t1;
	char DATA[2048]={'\0'};
	float OPTATE_MILLER=0,OPTATE_MILLER_NOT_USE_SPARSE=0,NORMAL_FINALEXP=0,OPTIMAL_FINALEXP1=0,FINALEXP_FEMALE_RESEARCHER=0,OPTIMAL_FINALEXP3=0,OPTATE_TOTAL=0;
	float NORMAL_G1_SCM=0,G1_SCM=0,NORMAL_G2_SCM=0,G2_SCM_2DIV=0,G2_SCM_4DIV=0,NORMAL_G3_EXP=0,G3_EXP=0;
	struct EFp12 P,Q,S1_P,S2_Q,Test1,Test2;
	EFp12_init(&P);
	EFp12_init(&Q);
	EFp12_init(&S1_P);
	EFp12_init(&S2_Q);
	EFp12_init(&Test1);
	EFp12_init(&Test2);
	struct Fp12 Z,result1,result2;
	Fp12_init(&Z);
	Fp12_init(&result1);
	Fp12_init(&result2);
	mpz_t S1,S2,S12;
	mpz_init(S1);
	mpz_init(S2);
	mpz_init(S12);
	
	FILE *fp;
	fp=fopen("BN12_result.csv","a");
	if(fp == NULL){
		printf("Couldn't open file\n");
	}
	
	//random scalar for P & Q
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	printf("*********scalar*********\n");
	mpz_urandomm(S1,state,EFp_order);	//S1
	printf("S1:");
	gmp_printf("%Zd",S1);
	printf("\n");
	mpz_urandomm(S2,state,EFp_order);	//S2
	printf("S2:");
	gmp_printf("%Zd",S2);
	printf("\n");
	mpz_mul(S12,S1,S2);			//S12
	mpz_mod(S12,S12,EFp_order);
	printf("S12:");
	gmp_printf("%Zd",S12);
	printf("\n\n");
	
	//set P & Q
	printf("*********G1 & G2*********\n");
	Fp12_set_ui(&P.x,0);
	mpz_set_str(P.x.x0.x0.x0.x0,"3689638845428621859038789527140362873539595807516056466770197411136365225625631648167486765494556214665733027042028983176256732062701265924",10);
	Fp12_set_ui(&P.y,0);
	mpz_set_str(P.y.x0.x0.x0.x0,"317144540373475318017372512885150399248464913485594622001811923402468697374856815380497703183867201796539650332677705339429260499085921798",10);
	
	EFp12_printf(&P,"P:");
	printf("\n");
	
	Fp12_set_ui(&Q.x,0);
	mpz_set_str(Q.x.x1.x1.x0.x0,"1461687820251057288645110453728211414842396739739866662058053920938551518213051582685563604554567210116303771967840691513754472421586822819",10);
	mpz_set_str(Q.x.x1.x1.x1.x0,"6003560508126326811274235936958614018421477421324559722831685716174519354650128702338452418192461284179010611195655903720837824169130548539",10);
	Fp12_set_ui(&Q.y,0);
	mpz_set_str(Q.y.x0.x1.x0.x0,"5155219793361950561247630307369686750650470040686652539353899009103066689907802951516641536559745363461355513907243381162214948894687249280",10);
	mpz_set_str(Q.y.x0.x1.x1.x0,"1998191902277703228076129918599031812774218833429468258790319261817022072256741879882572913951359490604605360263700257284455411784382947926",10);
	
	EFp12_printf(&Q,"Q:");
	printf("\n\n");
	
	//check infinite
	EFp12_SCM(&Test1,&P,EFp_order);
	EFp12_SCM(&Test2,&Q,EFp12_total);
	printf("[order]P:");
	if(Test1.flag==1){
		printf("infinite\n");
	}else{
		printf("not infinite\n");
	}
	printf("[order]Q:");
	if(Test2.flag==1){
		printf("infinite\n");
	}else{
		printf("not infinite\n");
	}
	printf("\n");
	
	printf("*********calculate [S1]P,[S2]Q*********\n");
	printf("G1 SCM\n");
	//NORMAL_G1_SCM
	gettimeofday(&t0,NULL);
	EFp12_G1_SCM_normal(&S1_P,&P,S1);			//S1_P
	gettimeofday(&t1,NULL);
	printf("normal G1 time:%.2f[ms]\n",NORMAL_G1_SCM=timedifference_msec(t0,t1));
	//G1_SCM
	gettimeofday(&t0,NULL);
	EFp12_G1_SCM(&S1_P,&P,S1);			//S1_P
	gettimeofday(&t1,NULL);
	printf("G1 time:%.2f[ms]\n\n",G1_SCM=timedifference_msec(t0,t1));
	
	printf("G2 SCM\n");
	//NORMAL_G2_SCM
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_normal(&S2_Q,&Q,S2);		//S2_Q
	gettimeofday(&t1,NULL);
	printf("normal G2 time:%.2f[ms]\n",NORMAL_G2_SCM=timedifference_msec(t0,t1));
	//G2_SCM_2DIV
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_2div(&S2_Q,&Q,S2);		//S2_Q
	gettimeofday(&t1,NULL);
	printf("2div G2 time:%.2f[ms]\n",G2_SCM_2DIV=timedifference_msec(t0,t1));
	//G2_SCM_4DIV
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_4div(&S2_Q,&Q,S2);		//S2_Q
	gettimeofday(&t1,NULL);
	printf("4div G2 time:%.2f[ms]\n\n",G2_SCM_4DIV=timedifference_msec(t0,t1));
	
	
	printf("*********opt-ate [S1]P,[S2]Q*********\n");
	
	//OPTATE_MILLER_NOT_
	
	//OPTATE_MILLER & FINALEXP_1 & OPTATE_TOTAL
	//void Opt_ate_pairing_return_time(struct Fp12 *ANS,struct EFp12 *Q,struct EFp12 *P,float *total,float *miller,float *finalexp1,float *finalexp3,float *normal_finalexp){
	Opt_ate_pairing_return_time(&Z,&Q,&P,&OPTATE_TOTAL,&OPTATE_MILLER,&OPTIMAL_FINALEXP1,&OPTIMAL_FINALEXP3,&NORMAL_FINALEXP);
	//Opt_ate_pairing(&Z,&Q,&P);
	printf("\n");
	
	//printf("*************linarity test***********\n");
	
	printf("G3 EXP\n");
	//NORMAL_G3_SCM
	gettimeofday(&t0,NULL);
	Fp12_pow(&result1,&Z,S12);						//Test1 Z^S12
	gettimeofday(&t1,NULL);
	printf("normal G3 time:%.2f[ms]\n",NORMAL_G3_EXP=timedifference_msec(t0,t1));
	//G3_EXP
	gettimeofday(&t0,NULL);
	Fp12_G3_pow(&result1,&Z,S12);						//Test1 Z^S12
	gettimeofday(&t1,NULL);
	printf("G3 time:%.2f[ms]\n\n",G3_EXP=timedifference_msec(t0,t1));
	
	//Opt_ate_pairing(&result2,&S2_Q,&S1_P);
	
	/*Fp12_printf(&result1,""); printf("\n");
	Fp12_printf(&result2,""); printf("\n");
	if(Fp12_cmp_zero(&result1)!=0 && Fp12_cmp_one(&result1)!=0 && Fp12_cmp(&result1,&result2)==0){
		printf("success\n\n");
	}else{
		printf("test failed\n\n");
	}*/
	
	fprintf(fp,"OPTATE_MILLER,OPTIMAL_FINALEXP,TOTALTIME\n%.2f,%.2f,%.2f\n",OPTATE_MILLER,OPTIMAL_FINALEXP3,OPTATE_TOTAL);
	fprintf(fp,"NORMAL_FINALEXP,OPTIMAL_FINALEXP1,OPTIMAL_FINALEXP3\n%.2f,%.2f,%.2f\n",NORMAL_FINALEXP,OPTIMAL_FINALEXP1,OPTIMAL_FINALEXP3);
	fprintf(fp,"NORMAL_G1_SCM,G1_SCM\n%.2f,%.2f\n",NORMAL_G1_SCM,G1_SCM);
	fprintf(fp,"NORMAL_G2_SCM,G2_SCM_2DIV,G2_SCM_4DIV\n%.2f,%.2f,%.2f\n",NORMAL_G2_SCM,G2_SCM_2DIV,G2_SCM_4DIV);
	fprintf(fp,"NORMAL_G3_EXP,G3_EXP\n%.2f,%.2f\n",NORMAL_G3_EXP,G3_EXP);
	
	
	fclose(fp);
	mpz_clear(S1);
	mpz_clear(S2);
	mpz_clear(S12);
	EFp12_clear(&P);
	EFp12_clear(&Q);
	EFp12_clear(&S1_P);
	EFp12_clear(&S2_Q);
	EFp12_clear(&Test1);
	EFp12_clear(&Test2);
	Fp12_clear(&Z);
	Fp12_clear(&result1);
	Fp12_clear(&result2);
}
/*============================================================================*/
/* test                                                                       */
/*============================================================================*/
void test_ate_pairing(){
	printf("====================================================================================\n");
	printf("Ate pairing\n\n");
	struct timeval t0,t1;
	struct EFp12 P,Q,S1_P,S2_P,S1_Q,S2_Q;
	EFp12_init(&P);
	EFp12_init(&Q);
	EFp12_init(&S1_P);
	EFp12_init(&S2_P);
	EFp12_init(&S1_Q);
	EFp12_init(&S2_Q);
	struct Fp12 Z,Test1,Test2,Test3;
	Fp12_init(&Z);
	Fp12_init(&Test1);
	Fp12_init(&Test2);
	Fp12_init(&Test3);
	mpz_t S1,S2,S12;
	mpz_init(S1);
	mpz_init(S2);
	mpz_init(S12);
	
	//S
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	printf("*********scalar*********\n");
	mpz_urandomm(S1,state,EFp_order);	//S1
	printf("S1:");
	gmp_printf("%Zd",S1);
	printf("\n");
	mpz_urandomm(S2,state,EFp_order);	//S2
	printf("S2:");
	gmp_printf("%Zd",S2);
	printf("\n");
	mpz_mul(S12,S1,S2);			//S12
	mpz_mod(S12,S12,EFp_order);
	printf("S12:");
	gmp_printf("%Zd",S12);
	printf("\n\n");
	
	printf("*********G1 & G2*********\n");
	EFp12_generate_G1(&P);			//P
	EFp12_printf(&P,"P:");
	printf("\n");
	EFp12_generate_G2(&Q);			//Q
	EFp12_printf(&Q,"Q:");
	printf("\n\n");
	
	printf("*********calculate [S1]P,[S2]P,[S1]Q,[S2]Q*********\n");
	EFp12_G1_SCM(&S1_P,&P,S1);			//S1_P
	EFp12_G1_SCM(&S2_P,&P,S2);			//S2_P
	EFp12_G2_SCM_2div(&S1_Q,&Q,S1);		//S1_Q
	EFp12_G2_SCM_2div(&S2_Q,&Q,S2);		//S2_Q
	printf("\n");
	
	printf("--------------------------------opt ate---------------------------------\n");
	gettimeofday(&t0,NULL);
	Opt_ate_pairing(&Z,&Q,&P);
	gettimeofday(&t1,NULL);
	printf("total time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	
	//linary test
	printf("*********linearity test**********\n");
	Fp12_pow(&Test1,&Z,S12);					//Test1 Z^S12
	Opt_ate_pairing(&Test2,&S2_Q,&S1_P);	//Test2 S1_P,S2_Q
	Fp12_printf(&Test2,""); printf("\n");
	Opt_ate_pairing(&Test3,&S1_Q,&S2_P);	//Test3 S2_Q,S1_P
	Fp12_printf(&Test3,""); printf("\n");
	printf("*********************************\n");
	if(Fp12_cmp(&Test1,&Fp12_ZERO)!=0 && Fp12_cmp(&Test1,&Fp12_ONE)!=0 && Fp12_cmp(&Test1,&Test2)==0 && Fp12_cmp(&Test2,&Test3)==0 && Fp12_cmp(&Test3,&Test1)==0){
		printf("test success\n\n");
	}else{
		printf("test failed\n\n");
	}
	
	printf("---------------------------------X ate----------------------------------\n");
	gettimeofday(&t0,NULL);
	X_ate_pairing(&Z,&Q,&P);
	gettimeofday(&t1,NULL);
	printf("total time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	
	//linary test
	printf("*********linearity test**********\n");
	Fp12_pow(&Test1,&Z,S12);					//Test1 Z^S12
	X_ate_pairing(&Test2,&S2_Q,&S1_P);	//Test2 S1_P,S2_Q
	Fp12_printf(&Test2,""); printf("\n");
	X_ate_pairing(&Test3,&S1_Q,&S2_P);	//Test3 S2_Q,S1_P
	Fp12_printf(&Test3,""); printf("\n");
	printf("*********************************\n");
	if(Fp12_cmp(&Test1,&Fp12_ZERO)!=0 && Fp12_cmp(&Test1,&Fp12_ONE)!=0 && Fp12_cmp(&Test1,&Test2)==0 && Fp12_cmp(&Test2,&Test3)==0 && Fp12_cmp(&Test3,&Test1)==0){
		printf("test success\n\n");
	}else{
		printf("test failed\n\n");
	}
	
	mpz_clear(S1);
	mpz_clear(S2);
	mpz_clear(S12);
	EFp12_clear(&P);
	EFp12_clear(&Q);
	EFp12_clear(&S1_P);
	EFp12_clear(&S2_P);
	EFp12_clear(&S1_Q);
	EFp12_clear(&S2_Q);
	Fp12_clear(&Z);
	Fp12_clear(&Test1);
	Fp12_clear(&Test2);
	Fp12_clear(&Test3);
}
void test_G1_SCM(){
	printf("====================================================================================\n");
	printf("G1 SCM\n\n");
	struct timeval t0,t1;
	struct EFp12 P,Test1,Test2;
	EFp12_init(&P);
	EFp12_init(&Test1);
	EFp12_init(&Test2);
	mpz_t S;
	mpz_init(S);
	
	//S
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	mpz_urandomm(S,state,EFp_order);
	printf("*********scalar*********\n");
	printf("S:");
	gmp_printf("%Zd",S);
	printf("\n\n");
	//G1
	EFp12_generate_G1(&P);
	
	printf("-------------------------------nomal G1 scm--------------------------------\n");
	gettimeofday(&t0,NULL);
	EFp12_G1_SCM_normal(&Test1,&P,S);
	gettimeofday(&t1,NULL);
	EFp12_printf(&Test1,"RESULT:"); printf("\n");
	printf("normal scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	num=0;
	printf("---------------------------------G1 scm--------------------------------\n");
	gettimeofday(&t0,NULL);
	EFp12_G1_SCM(&Test2,&P,S);
	gettimeofday(&t1,NULL);
	EFp12_printf(&Test2,"RESULT"); printf("\n");
	printf("G1 scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	printf("num of Fp multiplication:%ld\n",num);
	mpz_clear(S);
	EFp12_clear(&P);
	EFp12_clear(&Test1);
	EFp12_clear(&Test2);
}
void test_G2_SCM(){
	printf("====================================================================================\n");
	printf("G2 SCM\n\n");
	struct timeval t0,t1;
	struct EFp12 Q,Test1,Test2;
	EFp12_init(&Q);
	EFp12_init(&Test1);
	EFp12_init(&Test2);
	mpz_t S;
	mpz_init(S);
	
	//S
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	mpz_urandomm(S,state,EFp_order);
	printf("*********scalar*********\n");
	printf("S:");
	gmp_printf("%Zd",S);
	printf("\n\n");
	//G2
	EFp12_generate_G2(&Q);
	
	printf("-------------------------------nomal G2 scm--------------------------------\n");
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_normal(&Test1,&Q,S);
	gettimeofday(&t1,NULL);
	EFp12_printf(&Test1,"RESULT:"); printf("\n");
	printf("normal scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	
	printf("------------------------------G2 scm(2div)------------------------------\n");
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_2div(&Test2,&Q,S);
	gettimeofday(&t1,NULL);
	EFp12_printf(&Test2,"RESULT:"); printf("\n");
	printf("G2 scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	num=0;
	printf("------------------------------G2 scm(4div)------------------------------\n");
	gettimeofday(&t0,NULL);
	EFp12_G2_SCM_4div(&Test2,&Q,S);
	gettimeofday(&t1,NULL);
	EFp12_printf(&Test2,"RESULT:"); printf("\n");
	printf("G2 scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	printf("num of Fp multiplication:%ld\n",num);
	mpz_clear(S);
	EFp12_clear(&Q);
	EFp12_clear(&Test1);
	EFp12_clear(&Test2);
}
void test_G3_pow(){
	printf("====================================================================================\n");
	printf("G3 pow\n\n");
	struct timeval t0,t1;
	struct EFp12 P,Q,S1_P,S2_Q;
	EFp12_init(&P);
	EFp12_init(&Q);
	EFp12_init(&S1_P);
	EFp12_init(&S2_Q);
	struct Fp12 Z,Test1,Test2;
	Fp12_init(&Z);
	Fp12_init(&Test1);
	Fp12_init(&Test2);
	mpz_t S1,S2,S12;
	mpz_init(S1);
	mpz_init(S2);
	mpz_init(S12);
	
	//S
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned long)time(NULL));
	printf("*********scalar*********\n");
	mpz_urandomm(S1,state,EFp_order);	//S1
	printf("S1:");
	gmp_printf("%Zd",S1);
	printf("\n");
	mpz_urandomm(S2,state,EFp_order);	//S2
	printf("S2:");
	gmp_printf("%Zd",S2);
	printf("\n");
	mpz_mul(S12,S1,S2);			//S12
	mpz_mod(S12,S12,EFp_order);
	printf("S12:");
	gmp_printf("%Zd",S12);
	printf("\n\n");
	
	printf("*********G1 & G2*********\n");
	EFp12_generate_G1(&P);			//P
	EFp12_printf(&P,"P:");
	printf("\n");
	EFp12_generate_G2(&Q);			//Q
	EFp12_printf(&Q,"Q:");
	printf("\n\n");
	
	printf("*********calculate [S1]P,[S2]Q*********\n");
	EFp12_G1_SCM(&S1_P,&P,S1);		//S1_P
	EFp12_G2_SCM_2div(&S2_Q,&Q,S2);	//S2_Q
	printf("\n");
	
	printf("*********opt ate(Q,P)*********\n");
	gettimeofday(&t0,NULL);
	Opt_ate_pairing(&Z,&Q,&P);
	gettimeofday(&t1,NULL);
	printf("total time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	
	printf("*********opt ate(s2Q,s1P)*********\n");
	Opt_ate_pairing(&Test1,&S2_Q,&S1_P);	//Test2 S1_P,S2_Q
	Fp12_printf(&Test1,""); printf("\n\n");
	
	printf("-------------------------------nomal power--------------------------------\n");
	gettimeofday(&t0,NULL);
	Fp12_pow(&Test2,&Z,S12);					//Test1 Z^S12
	gettimeofday(&t1,NULL);
	Fp12_printf(&Test2,""); printf("\n");
	printf("normal scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	printf("---------------------------------G3 power---------------------------------\n");
	gettimeofday(&t0,NULL);
	Fp12_G3_pow(&Test2,&Z,S12);
	gettimeofday(&t1,NULL);
	Fp12_printf(&Test2,""); printf("\n");
	printf("normal scm time:%.2f[ms]\n\n",timedifference_msec(t0,t1));
	
	mpz_clear(S1);
	mpz_clear(S2);
	mpz_clear(S12);
	EFp12_clear(&P);
	EFp12_clear(&Q);
	EFp12_clear(&S1_P);
	EFp12_clear(&S2_Q);
	Fp12_clear(&Z);
	Fp12_clear(&Test1);
	Fp12_clear(&Test2);
}
