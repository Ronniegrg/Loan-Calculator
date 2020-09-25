//#pragma once

// A helper that discards all characters from stdin
void flush_me();

// prototype to display the menu
int menu(double principal, double rate, int years);

// prototype for principal update
double update_principal(double *loan_payment);

// prototype for updated rate
double update_rate(double *loan_payment);

// prototype for duration update
int update_duration(double *loan_payment);

// prototype for loan calculation payment
double calculate_loan_payment(double principal, double rate, int years);

// prototype for display loan payment
void display_loan_payment(const double *loan_payment, double principal,
                          double rate, int years);
