/**
    FILENAME: main.c
    AUTHOR: Rouni GORGEES
    DATE: August 17, 2018
    DESCRIPTION: The program that lets the user enter the principal, annual interest rate,
                 and number of years duration of a loan. The user can then choose to
                 find out what the monthly payment will be and/or print out a loan repayment table.
                 The program allows the user to change the values for the principal, annual interest rate,
                 and number of years duration without re-running the program
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main_prototypes.h"

enum {
    /* Constant menu identifiers */
    MENU_UPD_PRINCIPAL = 1, // update principal constant
    MENU_UPD_RATE, // update rate constant
    MENU_UPD_DURATION,// update duration constant
    MENU_CALC_PAYMENT, // calculate Payment
    MENU_DISP_PAYMENT,// display payment
    MENU_QUIT = 0, // quit the menu
    MENU_INIT = -1 // initialize variable to -1
};

/**
    the function that discard all characters from stdin
*/
void flush_me() {

    // declare integer c
    int c;
    // checking for error
    if (ferror(stdin))
        clearerr(stdin);

    // using while loop to check for new line
    // and end-of-file if not Ignore each character
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Ignore each character */
    }
}

int main(void) {
    // declare variable int choice
    int choice;
    // declare double principal and initialize it to -1
    double principal = -1.0;
    // declare and initialize double rate to -1
    double rate = -1.0;
    // declare and initialize double loan_payment to -1
    double loan_payment = -1.0;
    // declare integer year and initialize it to -1
    int years = -1;

    // initialize int choice to MENU_INIT which is equal to -1
    choice = MENU_INIT;
    // while choice is not equal to 0
    while (choice != MENU_QUIT) {
        // choice = menu function which reads
        // user input to determine in which
        // of variable we should do update (principal, rate, years).
        choice = menu(principal, rate, years);
        // if choice = MENU_UPD_RPINCIPAL which is equal to 1
        if (choice == MENU_UPD_PRINCIPAL)
            // set principle to update_principle
            // which is loan_payment
            principal = update_principal(&loan_payment);
        // if choice = 2 which is MENU_UPD_RATE
        if (choice == MENU_UPD_RATE)
            // then set the rate to update_rate
            // which will update the rate of the loan_payment
            rate = update_rate(&loan_payment);
        // if choice = 3 which is MENU_UPD_DURATION
        if (choice == MENU_UPD_DURATION)
            // set years to update_duration() function
            // which will update the duration of the loan payment
            years = update_duration(&loan_payment);
        // if choice = 4 which is MENY_CALC_PAYMENT
        if (choice == MENU_CALC_PAYMENT)
            // set the loan_payment to calculate_loan_payment()function
            loan_payment = calculate_loan_payment(principal, rate, years);
        // if choice = 5 which MENU_DISP_PAYMENT
        if (choice == MENU_DISP_PAYMENT)
            // calling display_loan_payment() function
            display_loan_payment(&loan_payment, principal, rate, years);
    }
    return 0;
}

/**
    menu function displays the options that the user
    has to choose ( 6 options) with displaying the current update for
    (principle, rate , and years)
*/
int menu(double principal, double rate, int years) {
    // declare variables
    int choice, input_choice;

    /* display the menu */
    printf("Big Bank Loan Calculator\n\n");
    // checking the value of the principal is greater than zero. if so
    if (principal > 0)
        // set and print the update principal value
        printf("%d. Update principal (currently $%.2f)\n", MENU_UPD_PRINCIPAL,
               principal);
    else
        // set the principal value to not set
        printf("%d. Update principal (currently %s)\n", MENU_UPD_PRINCIPAL,
               "not set");
    // checking if the rate value is greater than zero
    if (rate > 0)
        // set and print the updated value on annual interest rate
        printf("%d. Update annual interest rate (currently %.2f%%)\n",
               MENU_UPD_RATE, rate);
    else
        // set updated annual interest rate value to not set
        printf("%d. Update annual interest rate (currently %s)\n",
               MENU_UPD_RATE, "not set");
    // check if the year value is greater than zero
    if (years > 0)
        // set and display the updated value of duration of loan (in years)
        printf("%d. Update duration of loan (currently %d yrs)\n",
               MENU_UPD_DURATION, years);
    else
        // set updated duration of loan to not set if the value is less than zero
        printf("%d. Update duration of loan (currently %s)\n",
               MENU_UPD_DURATION, "not set");
    printf("%d. Calculate loan payment\n", MENU_CALC_PAYMENT);
    printf("%d. Display loan repayment table\n", MENU_DISP_PAYMENT);
    printf("\n");
    printf("%d. Quit\n", MENU_QUIT);
    printf("\n");

    /* Get and validate the response from a user */
    // initialize input_value to zero
    input_choice = 0;
    while (input_choice == 0) {
        printf("?> ");
        /* IMPORTANT: variable is passed to scanf() through pointers */
        input_choice = scanf("%d", &choice);
        // checking  the input_value
        if (input_choice == 0) {
            printf("Type error, try again.\n");
        } else if (input_choice == EOF) {
            printf("Input error, try again.\n");
            // checking if the choice is less than 0 and greater than 5
        } else if ((choice < 0) || (choice > 5)) {
            // if so, print the message
            printf("Please, try again.\n");
            // set input_value to 0
            input_choice = 0;
        }
        // calling flush_me() function
        flush_me();
    }
    // return choice
    return choice;
}

/**
    the function update_principal updates the value of the
    principal paid. the function accepts double pointer value
    then calculates and return the principal
*/
double update_principal(double *loan_payment) {
    // declare variable
    double principal;
    int input_principal;

    /* IMPORTANT: the load payment is reset through pointers */
    if (!loan_payment) {
        puts("\nUnavailable.");
        return -1;
    }

    /* Ask and validate a value */
    printf("\nEnter the new principal value.\n");
    // initialize input_principal to 0
    input_principal = 0;
    while (input_principal == 0) {
        printf("?> ");
        // store user input value in input_principal
        input_principal = scanf("%lf", &principal);
        // if the input_principal value is 0
        if (input_principal == 0) {
            // display error message and ask the user to try again
            printf("Type error, try again.\n");
            // if it is the end-of-file
        } else if (input_principal == EOF) {
            // display input error message and ask the user to try again
            printf("Input error, try again.\n");
            // checking if the input_principal is positive
        } else if (principal <= 0) {
            // display validation message and ask use to try again
            printf("Must be positive, try again.\n");
            // set input_principal to 0
            input_principal = 0;
        }
        // calling flush_me() function
        flush_me();
    }
    // set loan_payment value to -1
    *loan_payment = -1;
    // return principal
    return principal;
}

/**
    update_rate function update the monthly interest rate
    by asking the user to enter input_rate. the function
    accepts double pointers value the it return the rate
*/
double update_rate(double *loan_payment) {

    // declare variables
    double rate;
    int input_rate;

    /* IMPORTANT: the load payment is reset through pointers */
    if (!loan_payment) {
        puts("\nUnavailable.");
        return -1;
    }

    /* Ask and validate a value */
    printf("\nEnter the new annual rate (in percent).\n");
    // initialize input_rate to 0
    input_rate = 0;
    while (input_rate == 0) {
        printf("?> ");
        // store user's input in input_rate value
        input_rate = scanf("%lf", &rate);
        // checking input_rate if it is equal to 0
        if (input_rate == 0) {
            // display error message and ask user to try again
            printf("Type error, try again.\n");
            // check if it is end-of-file
        } else if (input_rate == EOF) {
            // display input error and ask user to try again
            printf("Input error, try again.\n");
            // checking int the rate is positive
        } else if (rate <= 0) {
            // display message and inform user than the input
            // must be positive and ask user to try again
            printf("Must be positive, try again.\n");
            // set input_rate to 0
            input_rate = 0;
            // check if the rate is greater than 50
        } else if (rate > 50) {
            // display message and inform the user about the limitation of the rate
            printf("Must be less or equal than 50, try again.\n");
            // set input_rate to 0
            input_rate = 0;
        }
        // calling flush_me() function
        flush_me();
    }
    // set loan_payment pointer to -1
    *loan_payment = -1;
    // return rate
    return rate;
}

/**
    update_duration function update the number of the years
    of the loan payment. the function accepts double pointers values
    which return the number of year(year)
*/
int update_duration(double *loan_payment) {
    int years;
    int input_years;

    /* IMPORTANT: the load payment is reset through pointers */
    if (!loan_payment) {
        puts("\nUnavailable.");
        return -1;
    }

    /* Ask and validate a value */
    printf("\nEnter the new duration period (in years).\n");
    // initialize input_years to 0
    input_years = 0;
    while (input_years == 0) {
        printf("?> ");
        // store user input in input_year variable
        input_years = scanf("%d", &years);
        // check input_years
        if (input_years == 0) {
            // display error message and ask user to try again
            printf("Type error, try again.\n");
            // if input_years equal end-of-file
        } else if (input_years == EOF) {
            // display input error message and ask user to try again
            printf("Input error, try again.\n");
            // check if the years value is positive
        } else if (years <= 0) {
            // display error message and inform the user
            // that the value must be positive and
            // ask the user to try again
            printf("Must be positive, try again.\n");
            // set input_years to 0
            input_years = 0;
            // check if the value of years is greater than 75
        } else if (years > 75) {
            // display message and inform the user that
            // the value must be less or equal than 75
            printf("Must be less or equal than 75, try again.\n");
            // set input_years to 0
            input_years = 0;
        }
        // calling flush_me() function
        flush_me();
    }
    // set loan_payment pointer to -1
    *loan_payment = -1;
    // return years
    return years;
}
/**
    calculate_loan_payment function calculates and return loan_payment.
    The function accepts three variables two double type and one integer
    type.
*/
double calculate_loan_payment(double principal, double rate, int years) {

    // declare and initialize monthly_interest_rate
    double monthly_interest_rate = rate / 100 / 12;
    // declare and set months to years multiplied by 12
    int months = years * 12;
    // declare double loan_payment variable
    double loan_payment;
    // check if (principal , rate, and years) not greater than 0
    if (!((principal > 0) && (rate > 0) && (years > 0))) {
        puts("\nUnavailable.");
        // set loan_payment to -1
        loan_payment = -1;
    } else {
        // calculate loan_payment
        loan_payment = principal * monthly_interest_rate / (1 - pow(1 + monthly_interest_rate, -months));
        // display the output of the loan_payment
        printf("\nThe loan payment is %.2f\n", loan_payment);
    }
    // return loan_payment
    return loan_payment;
}
/**
    display_loan_payment function displays the table of the final
    output of the entire calculation
*/
void display_loan_payment(const double *loan_payment, double principal,
                          double rate, int years) {
    // declare and initialize variables
    time_t when;
    int i, j, month;
    double interest_paid, principal_paid, old_balance, new_balance;
    double monthly_interest_rate = rate / 100 / 12;

    /* IMPORTANT: the load payment is read through pointers */
    if (!((loan_payment != 0 && (*loan_payment > 0)) && (principal > 0) && (rate > 0) && (years > 0))) {
        puts("\nUnavailable.");
        when = time(0) + 1;
        while (time(0) < when) {
            /* Wait 1 second */
        }
        return;
    }

    /* The function is paused for 12 seconds after every year iteration */
    new_balance = principal;
    // initialize month to 0
    month = 0;
    // printing the hears of the table
    printf("\n%5s %17s %11s %12s %12s %14s\n", "Month", "Old Balance",
           "Payment", "Interest", "Principal", "New Balance");
    // using nested for loop to calculate the values
    for (i = 0; i < years; i++) {
        for (j = 0; j < 12; j++) {
            // setting old_balance to new_balance
            old_balance = new_balance;
            // increase month value by 1
            month++;
            // calculate interest_paid
            interest_paid = old_balance * monthly_interest_rate;
            // calculate principal_paid
            principal_paid = *loan_payment - interest_paid;
            // calculate new_balance
            new_balance = old_balance - principal_paid;
            // display the output of the entire calculation through the table
            printf("%4d  %16.2f  %10.2f  %11.2f  %11.2f  %13.2f\n", month,
                   old_balance, *loan_payment, interest_paid, principal_paid,
                   new_balance);
        }

        fflush(stdout);
        when = time(0) + 12;
        while (time(0) < when) {
            /* Wait 12 seconds */
        }
    }
}
