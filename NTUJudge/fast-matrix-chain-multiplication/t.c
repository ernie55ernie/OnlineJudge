// Matrix chain multiplications.
// Input: sequence of matrix dimens, end in 0.
#include <stdio.h>
#define L 15  // big enough for most examples

int r(int i, int j, int s[L][L]);  // print =s
void putpre(int x);                // used by r
void putdig(int x);                // used by r
int newtemp(void);                 // used by r
void r2(int i, int j, int s[L][L]);// print par
void r3(int i, int j, int s[L][L]);// expression

void main(void) {
   int p[L];     // input array of dimensions
   int m[L][L];  // array of numbers of mults
   int s[L][L];  // array giving index opt sol
   int n = 0, i, ll, j, k, q;
   int res; // final result from seq of assigns
   for (i = 0; i < L; i++) {
      scanf("%i", &p[i]); // read up to a zero
      if (p[i] <= 0) break;
   }
   n = i - 1;
   // calculate matices m and s
   for (i = 1 ; i <= n; i++)
      m[i][i] = 0;
   for (ll = 2; ll <= n; ll++)
      for (i = 1; i <= n - ll + 1; i++) {
         j = i + ll - 1;
         m[i][j] = 444444444; // "infinity"
         for (k = i; k <= j - 1; k++) {
            q = m[i][k] + m[k+1][j] +
               p[i-1]*p[k]*p[j];
            if (q < m[i][j]) {
               m[i][j] = q;
               s[i][j] = k;
            }
         }
      }
   // print p
   printf("The array p:\n\n");
   for (i = 0; i <= n; i++)
      printf("p[%i] =%3i, ", i, p[i]);
   // print m
   printf("\n\nThe array m:\n\n       ");
   for (i = 1; i <= n; i++)
      printf(" i=%2i  ", i);
   printf("\n");
   for (j = n; j >= 1; j--) {
      printf("j=%2i:", j);
      for (i = 1; i <= j; i++)
         printf("%7i", m[i][j]);
      printf("\n");
   }
   // print s
   printf("\nThe array s:\n\n       ");
   for (i = 1; i < n; i++)
      printf(" i=%2i  ", i);
   printf("\n");
   for (j = n; j >= 2; j--) {
      printf("j=%2i:", j);
      for (i = 1; i < j; i++)
         printf("%7i", s[i][j]);
      printf("\n");
   }
   printf("\n");
   res = r(1, n, s);
   printf("Final result is in T");
   putdig(res); printf("\n\n");
   r2(1, n, s); printf("\n\n");
   r3(1, n, s); printf("\n");
}
   // r: function that calcs series of assigns
int r(int i, int j, int s[L][L]) {
   int k, arg1, arg2, res;
   if (i == j) return i;
   k = s[i][j];         // top-level split
   arg1 = r(i, k, s);   // temp left half
   arg2 = r(k+1, j, s); // temp right half
   res = -newtemp();    // next temp
   // a negative number indicates a temp
   // next three lines output one equation
   putpre(res); putdig(res); putchar('=');
   putpre(arg1);putdig(arg1);putchar('*');
   putpre(arg2);putdig(arg2);putchar('\n');
   return res;
}

// putpre: neg is a temp; pos if an arg
void putpre(int x) {
   if (x < 0) putchar('T');
   else putchar('A');
}

// putdigit: spit one digit, without sign
void putdig(int x) {
   if (x < 0) x = -x;
   printf("%i", x);
}

// newtemp: return next integer in order
int newtemp(void) {
   static i = 1;
   return i++;
}

// r2: output paren form with extra parens
void r2(int i, int j, int s[L][L]) {
   int k;
   if (i == j) {
      printf("A%i", i);
      return;
   }
   k = s[i][j];
   printf("(");
   r2(i, k, s);
   printf(")*(");
   r2(k+1, j, s);
   printf(")");
}

// r3: output paren form with fewer parens
void r3(int i, int j, int s[L][L]) {
   int k;
   if (i == j) {
      printf("A%i", i);
      return;
   }
   printf("(");
   k = s[i][j];
   r3(i, k, s);
   printf("*");
   r3(k+1, j, s);
   printf(")");
}