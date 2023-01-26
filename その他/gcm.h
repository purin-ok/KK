#if !defined(GCM_H)
#define GCM_H

/* 型 宣 言 */
typedef unsigned int u_int;

/* 関 数 形 式 マ ク ロ */
#define ABS(a) ((a) < 0 ? -(a) : (a))

/* 関 数 プ ロ ト タ イ プ 宣 言 */
u_int gcm(u_int, u_int);

#endif /* GCM_H */