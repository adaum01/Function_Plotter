// ECE 209 - Spring 2021
// Program 1: Plotting the values of a function
// Inputs provided on stdin by user, in this order:
//   size = number of stars in positive-y, negative-y, and x dimensions (int)
//   yrange = max. y value to be plotted (double)
//   xrange = max. x value to be plotted (double)
//   fn = function code (char) -- see program spec for details
// Function is plotted with y axis horizontal and x axis vertical.
// x always starts at value zero. The y zero value is in the middle of the plot.
//
// **** Alexander Daum, 2/18/21 ****
//


#include <stdio.h>
#include <math.h>
#include <string.h>

double findXCoord(int row, int sizeVal, double xrangeVal);
double findVal(double xCoord, double yrangeVal, char func);
int findStars(double value, int sizeVal, double yrangeVal);
void printXCoord(int numStars, double value, int sizeVal);

int main() {
    int size = -1;
    double yrange = 0., xrange = 0.;
    char fn = 'q';
    scanf("%d%lf%lf %c", &size, &yrange, &xrange, &fn);
    printf("size: %d, yrange: %.2f, xrange: %.2f, function: \'%c\'\n",
           size, yrange, xrange, fn);
    if ((size < 0) || (yrange < 0) || (xrange < 0)) {
        printf("Illegal input.\n");
        return 0;
    }
    if (strchr("mselz", fn) == NULL) {
        printf("Illegal function.\n");
        return 0;
    }

    for (int i=0; i < (2*size+1); i++){     //print hyphen line, followed by a newline
        printf("-");
    }
    printf("\n");

    for (int i = 0; i <= size; i++){                        //plot the graph row by row until row = size
        double xCoord = findXCoord(i, size, xrange);        //1. determine x-coordinate value of current row
        double value = findVal(xCoord, yrange, fn);         //2. use x-coordinate value to find associated y-value
        int numStars = findStars(value, size, yrange);      //3. determine number of stars necessary to represent y-value
        printXCoord(numStars, value, size);                 //4. use values to print out row of plot
    }
    return 0;
}


// computes proper x coordinate in relation to current row of plot and step size, returns double xCoord
// specify current row, size, and domain of plot
double findXCoord(int row, int sizeVal, double xrangeVal){
    double xCoord = row * (xrangeVal/sizeVal);        //multiply given row by the step increment
    return xCoord;
}


// finds value of given function at given x coordinate, returns double retVal
// specify x-coordinate (xCoord), yrange value, and function (func)
double findVal(double xCoord, double yrangeVal, char func){
    double retVal = 0;
    if (func == 'm'){
        retVal = (2 * xCoord)-yrangeVal;       //if input function is 'm', compute y=2x-c
    }
    else if (func == 's'){
        retVal = sin(xCoord);               //if input function is 's', compute y=sin(x)
    }
    else if (func == 'e'){
        retVal = exp(xCoord);               //if input function is 'e', compute y=e^x
    }
    else if (func == 'l'){
        if (xCoord == 0)                    //if input function is 'l', compute y=ln(x)
            retVal = 0;                     //HOWEVER if input val is zero, y=0
        else
            retVal = log(xCoord);
    }
    else if (func == 'z'){
        retVal = 0;                         //if input function is 'z', y=0
    }
    return retVal;
}


// finds the number of stars to be printed given a value, returns integer stars
// if the given value exceeds the yrange value, return the maximum size
// specify given input value, size value, and yrange value of plot
int findStars(double value, int sizeVal, double yrangeVal){
    if (value < 0)
        value *= -1;        //if input value is negative, make value positive

    int stars = round(value * (sizeVal/yrangeVal));       //set star equal to the nearest possible representation of star
    if (value > yrangeVal)
        stars = sizeVal;       //if value exceeds y-range, set stars to the max value of stars instead
    return stars;
}


// prints line of '.' and '*' to represent a given x-coordinate of a graph, returns nothing
// specify number of stars (numStars), determined input value, and size value of plot
void printXCoord(int numStars, double value, int sizeVal){
    int remain = sizeVal - numStars;       //out of the total value size, find how many are '.'

    if (value > 0){
        for (int i = 0; i < sizeVal; i++){      //if the value is greater than 0,
            printf(".");                //1. all negative y-coordinates are '.'
        }                                       //2. output zero '*'
        printf("*");                    //3. print out all determined '*' to the right of the zero '*'
        for (int i = 0; i < numStars; i++){     //4. fill out the remainder of y-coordinates up to the value size with '.'
            printf("*");                //5. once row is complete, begin a new row
        }
        for (int i = 0; i < remain; i++){
            printf(".");
        }
        printf("\n");
    }
    else if (value < 0){
        for (int i = 0; i < remain; i++){       //if value is less than 0,
            printf(".");                //1. output remainder '.' first
        }                                       //2. print out all determined '*' to complete negative y-coordinate portion of plot
        for (int i = 0; i < numStars; i++){     //3. output zero '*'
            printf("*");                //4. all positive y-coordinates are '.' up to the value size
        }                                       //5. once row is complete, begin new row
        printf("*");
        for (int i = 0; i < sizeVal; i++){
            printf(".");
        }
        printf("\n");
    }
    else{
        for (int i = 0; i < sizeVal; i++){      //if value is zero,
            printf(".");                //1. print '.' for all negative y-coordinates
        }                                       //2. output zero '*'
        printf("*");                    //3. print '.' for all positive y-coordinates
        for (int i = 0; i < sizeVal; i++){      //4. once row is complete, begin new row
            printf(".");
        }
        printf("\n");
    }
}
