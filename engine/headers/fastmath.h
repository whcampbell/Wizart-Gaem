#pragma once

#define PI 3.14159263

/**
 * Uses the legs of a right triangle to calculate cosine
 * 
 * float dx -   the x leg of the right triangle
 * float dy -   the y leg of the right triangle
 * returns  -   the cosine based on the input legs of a triangle
 */ 
float cos(float dx, float dy);

/**
 * Uses the legs of a right triangle to calculate cosine
 * 
 * float dx -   the x leg of the right triangle
 * float dy -   the y leg of the right triangle
 * returns  -   the sine based on the input legs of a triangle
 */
float sin(float dx, float dy);

/**
 * Uses the legs of a right triangle to calculate cosine
 * 
 * float dx -   the x leg of the right triangle
 * float dy -   the y leg of the right triangle
 * returns  -   the tangent based on the input legs of a triangle
 */
float tan(float dx, float dy);

/**
 * Uses the legs of a right triangle to an angle of the hypotenuse
 * 
 * float dx -   the x leg of the right triangle
 * float dy -   the y leg of the right triangle
 * returns  -   the angle (in degrees) of the hypotenuse from the baseline, based on the legs of the triangle
 */
int angle(float dx, float dy);