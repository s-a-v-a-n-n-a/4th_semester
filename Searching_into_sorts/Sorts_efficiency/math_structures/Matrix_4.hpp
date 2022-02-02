#ifndef MATRIX_4_CLASS
#define MATRIX_4_CLASS

typedef unsigned char ur;

const size_t MAX_MATRIX_4_SIZE = 4;

class Matrix_4
{
public:
	double elements[MAX_MATRIX_4_SIZE][MAX_MATRIX_4_SIZE];

	Matrix_4()
	{
		for (ur i = 0; i < MAX_MATRIX_4_SIZE; ++i)
		{
			for (ur j = 0; j < MAX_MATRIX_4_SIZE; ++j)
			{
				elements[i][j] = 0.0;
			}
		}
	}

	Matrix_4(const double par_elements[MAX_MATRIX_4_SIZE][MAX_MATRIX_4_SIZE])
	{
		set_elements(par_elements);
	}

	Matrix_4(const double par_elements[MAX_MATRIX_4_SIZE * MAX_MATRIX_4_SIZE])
	{
		for (ur i = 0; i < MAX_MATRIX_4_SIZE; ++i)
		{
			for (ur j = 0; j < MAX_MATRIX_4_SIZE; ++j)
			{
				elements[i][j] = par_elements[i * MAX_MATRIX_4_SIZE + j];
			}
		}
	}

	Matrix_4(const Matrix_4 &other)
	{
		set_elements(other.elements);
	}

	const Matrix_4& operator*=(const Matrix_4 &other)
	{
		Matrix_4 result_matrix;
 
	    for (ur i = 0; i < MAX_MATRIX_4_SIZE; ++i)
	    {
	        for (ur j = 0; j < MAX_MATRIX_4_SIZE; ++j)
	        {
	            ur k = 0;
	            for (ur l = 0; l < MAX_MATRIX_4_SIZE; ++l, ++k)
	            {
	                result_matrix.elements[i][j] += elements[i][l] * other.elements[k][j];
	            }
	        }
	    }

	    set_elements(result_matrix.elements);
	 
	    return *this;
	}

	void set_elements(const double array[MAX_MATRIX_4_SIZE][MAX_MATRIX_4_SIZE])
	{
		for (ur i = 0; i < MAX_MATRIX_4_SIZE; ++i)
		{
			for (ur j = 0; j < MAX_MATRIX_4_SIZE; ++j)
			{
				elements[i][j] = array[i][j];
			}
		}
	}
};

#endif // MATRIX_4_CLASS
