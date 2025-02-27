#ifndef HALTON_H_
#define HALTON_H_

#ifdef __cplusplus
extern "C" {
#endif

double arc_cosine ( double c );
double atan4 ( double y, double x );
char digit_to_ch ( int i );
int get_seed ( void );
int halham_leap_check ( int dim_num, int leap[] );
int halham_n_check ( int n );
int halham_dim_num_check ( int dim_num );
int halham_seed_check ( int dim_num, int seed[] );
int halham_step_check ( int step );
void halton ( double r[] );
int halton_base_check ( int dim_num, int base[] );
int *halton_base_get ( void );
void halton_base_set ( int base[] );
int *halton_leap_get ( void );
void halton_leap_set ( int leap[] );
int halton_dim_num_get ( void );
void halton_dim_num_set ( int dim_num );
int *halton_seed_get ( void );
void halton_seed_set ( int seed[] );
void halton_sequence ( int n, double r[] );
int halton_step_get ( void );
void halton_step_set ( int step );
int i4_log_10 ( int i );
int i4_min ( int i1, int i2 );
void i4_to_halton ( int dim_num, int step, int seed[], int leap[], int base[], 
  double r[] );
void i4_to_halton_sequence ( int dim_num, int n, int step, int seed[], int leap[],
  int base[], double r[] );
char *i4_to_s ( int i );
void i4vec_transpose_print ( int n, int a[], char *title );
int prime ( int n );
double r8_epsilon ( void );
double r8vec_dot_product ( int n, double *r1, double *r2 );
double r8vec_norm_l2 ( int n, double a[] );
int s_len_trim ( char *s );
void u1_to_sphere_unit_2d ( double u[1], double x[2] );
void u2_to_ball_unit_2d ( double u[2], double x[2] );
void u2_to_sphere_unit_3d ( double u[2], double x[3] );
void u3_to_ball_unit_3d ( double u[3], double x[3] );

#ifdef __cplusplus
}
#endif

#endif /* HALTON_H_ */
