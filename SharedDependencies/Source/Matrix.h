/*********************************************************************
 * @file   Matrix.h
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com)
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#pragma once

#include "Vector.h"

#include "CustomStringFunctions.h"

#include <cassert>

#define _USE_MATH_DEFINES
#include <math.h>

template<unsigned int Rows, unsigned int Columns>
class Matrix
{
public:

	Matrix() = default;

	Matrix(float Matrix[Rows][Columns])
		//: /*matrix(Matrix)*/
	{
		for (int i = 0; i < Rows; ++i)
		{
			for (int j = 0; j < Columns; ++j)
			{
				matrix[i][j] = Matrix[i][j];
			}
		}
	}

	/*Matrix& operator=(Matrix const& other)
	{
		for (int i = 0; i)
	}*/

	float const& operator[](unsigned int row, unsigned int column) const
	{
		return matrix[row][column];
	}

	float& operator[](unsigned int row, unsigned int column)
	{
		return matrix[row][column];
	}

	void Serialize(string* Output)
	{
		string& tempString = *Output;

		IncrementTab();

		tempString.append("Matrix<" + std::to_string(Rows) + "|" + std::to_string(Columns) + ">:\n");

		for (int i = 0; i < Rows; ++i)
		{
			tempString.append(Tab() + "[");

			for (int j = 0; j < Columns; ++j)
			{
				float tempf = matrix[i][j];
				tempString.append(std::to_string(tempf) + "|");
			}

			tempString.pop_back();
			tempString.append("]\n");
		}

		IncrementTab(-1);
	}

	constexpr unsigned int NumRows() { return Rows; }
	constexpr unsigned int NumColumns() { return Columns; }
	
		// This function sets the matrix equal to the identity matrix.
	constexpr void Identity()
	{
		if constexpr (Rows != Columns)
		{
			assert(0 && "Identity() can only be used on square matrices!");
		}

		for (int i = 0; i < Rows; ++i)
		{
			for (int j = 0; j < Columns; ++j)
			{
				matrix[i][j] = (i == j);
			}
		}
	}

	// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
	// (NOTE: Care must be taken when pResult = pMtx.)
	Matrix<Columns, Rows> GetTranspose()
	{
		auto newMatrix = Matrix<Columns, Rows>();

		for (int i = 0; i < Columns; ++i)
		{
			for (int j = 0; j < Rows; ++j)
			{
				newMatrix[i, j] = matrix[j][i];
			}
		}

		return newMatrix;
	}

	// This function creates a translation matrix from x & y and saves it in Result.
	void Translate(Vector<Columns> const& translation)
	{
		auto translationMatrix = Matrix();
		translationMatrix.Identity();
		
		for (int i = 0; i < Columns; ++i)
		{
			translationMatrix[i, Columns - 1] = translation[i];
		}

		this->ConcatInPlace(translationMatrix);
	}

	// This function creates a scaling matrix from x & y and saves it in Result.
	// (Hint: This function must initialize all matrix values.)
	void Scale(Vector<Columns> const& scaling)
	{
		auto scalingMatrix = Matrix();
		scalingMatrix.Identity();

		for (int i = 0; i < Columns; ++i)
		{
			scalingMatrix[i, i] = scaling[i];
		}

		this->ConcatInPlace(scalingMatrix);
	}

	// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
	// (Hint: This function must initialize all matrix values.)
	// Converting from degrees to radians can be performed as follows:
	//	 radians = (angle * M_PI) / 180.0f
	// M_PI is defined in "math.h", which may be included as follows:
	//   #define _USE_MATH_DEFINES
	//   #include <math.h>
	void RotDeg(float angle)
	{
		RotRad(angle * (float)M_PI / 180.f);
	}

	// This matrix creates a rotation matrix from "Angle" whose value is in radians.
	// (Hint: This function must initialize all matrix values.)
	void RotRad(float angle)
	{
		if constexpr (Rows != 4)
		{
			assert(0 && "Currently, all matrix rotations are performed around the Z axis, and expect a 4x4 matrix.");
		}

		auto rotationMatrix = Matrix();
		rotationMatrix.Identity();

		matrix[0][0] = cosf(angle);
		matrix[1][1] = cosf(angle);

		matrix[0][1] = -sinf(angle);
		matrix[1][0] = sinf(angle);

		this->ConcatInPlace(rotationMatrix);
	}

	// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
	// Result = Mtx0*Mtx1
	// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
	template<unsigned int OtherColumns>
	Matrix<Rows, OtherColumns> Concat(Matrix<Columns, OtherColumns> const& other)
	{
		auto concatMatrix = Matrix<Rows, OtherColumns>();

		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < OtherColumns; j++)
			{
				float total = 0;

				for (int k = 0; k < Columns; k++)
				{
					total += this->matrix[i][k] * other[i, j];
				}

				concatMatrix[i, j] = total;
			}
		}

		return concatMatrix;
	}

	void ConcatInPlace(Matrix const& other)
	{
		Matrix concatMatrix = Matrix();
		//concatMatrix.Identity();

		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Columns; j++)
			{
				float total = 0;

				for (int k = 0; k < Columns; k++)
				{
					total += this->matrix[i][k] * other[k, j];
				}

				concatMatrix[i, j] = total;
			}
		}

		*this = concatMatrix;
	}

	Vector<Columns> VectorProduct(Vector<Columns> const& other)
	{
		other;
	}

private:

	float matrix[Rows][Columns];

};
