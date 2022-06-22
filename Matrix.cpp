#include <iostream>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <iomanip>
using namespace std;
/* Class for operations on Matricies */
class Matrix
{
private:
    int row,col;
    float **matrix_array;

public:
    Matrix(int r=0,int c=0)    //class constructor,necessary to give arguments.
    {set(r,c);}

    void set(int r,int c)
    {
        if (setRow(r) && setCol(c))   // memory is allocated only when Row and Column are validated,else what is the need
            setArray();
    }

    void setArray()           // allocate the memory for array
    {
        matrix_array=(float **)calloc(getRow(),sizeof(int*));   // calloc is used because it can assign initial values to the array.
        for(int i=0;i<getRow();i++)
            matrix_array[i]=(float *)calloc(getCol(),sizeof(int));
    }

    float ** getArray()  const    // access the private matrix through getArray().
    {return matrix_array;}

    void inputArray()        // input the array.
    {
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {
                        cout<<"Enter element ["<<i+1<<"]["<<j+1<<"]   ";
                        cin>>getArray()[i][j];
                        cout<<endl;
                    }
            }
    }

    void showMatrix(int prec=3,int width=9)      // display the array.
    {
        for(int i=0;i<getRow();i++)
            {
                cout<<" [";
                for(int j=0;j<getCol();j++)
                    cout<<setprecision(prec)<<setw(width)<<getArray()[i][j]<<setw(width);
             cout<<"]"<<endl;
            }
        cout<<endl;
    }

    bool setRow(int r)       //returns true if row entered is validated successfully.
    {
        if(r<=0)
        {
            cout<<"Wrong Value Entered ! Terminating Program";
            return false;
            exit(3);
        }
        row=r;
        return true;
    }

    bool setCol(int c)     //returns true if column entered is validated successfully.
    {
     if(c<=0)
        {
            cout<<"Wrong Value Entered ! Terminating Program";
            return false;
            exit(3);     // if we ever remove this,then above statement will help to detect errors.
        }
        col=c;          //no need of else statement(as long as exit is used above!)
        return true;
    }

    ~Matrix()          //destructor of the class, when called,frees the memory of the matrix array.
    {
        for(int i=0;i<getRow();i++)
            free(getArray()[i]);
        free(getArray());
    }

    int getRow()  const            //access the private member row through get function.
    {return row;}

    int getCol()  const          //access the private member column through get function.
    {return col;}

    float Sum()            // returns the Sum of the elements of array.
    {
        float sum_arr=0.0;
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                sum_arr+=getArray()[i][j];
        }
        return sum_arr;
    }

    float Product()            // returns the Product of the elements of array.
    {
        float prod_arr=1.0;
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                prod_arr*=getArray()[i][j];
        }
        return prod_arr;
    }

    float Mean()       // returns the mean of the array
    {return Sum()/(getRow()*getCol());}

    float StdDev()   // calculates the standard deviation of the matrix
    {
        float psum=0;
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                psum+=pow((getArray()[i][j]-Mean()),2);
        }
        return psum/(getRow()*getCol());
    }

    float Min()      // returns the lowest element of the array.
    {
        float min_ele=getArray()[0][0];
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
            {
                if(getArray()[i][j]<min_ele)
                    min_ele=getArray()[i][j];
            }
        }
        return min_ele;
    }

    float Max()      // returns the lowest element of the array.
    {
        float max_ele=getArray()[0][0];
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
            {
                if(getArray()[i][j]>max_ele)
                    max_ele=getArray()[i][j];
            }
        }
        return max_ele;
    }

    float Trace()           // returns the sum of main diagonal of the matrix.
    {
        if (getCol()!=getRow())
            {
                cout<<"Trace is not compatiple for non-square matrix"<<endl;
                exit(3);
            }
        int ltrace=0;
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {
                        if(i==j)
                            ltrace+=getArray()[i][j];
                    }
            }

        return ltrace;
    }

    float RTrace()          // returns the sum of other diagonal of the matrix.
    {
        if (getCol()!=getRow())
            {
                cout<<"Trace is not compatiple for non-square matrix"<<endl;
                exit(3);
            }
        int rtrace=0;
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {
                        if(i==getRow()-1-j)
                            rtrace+=getArray()[i][j];
                    }
            }

        return rtrace;
    }

    float Determinant()     // returns the determinant of the matrix.
    {
        if (getRow()!=getCol())
            {
                cout<<"Determinant is incompatible for the given martix"<<endl;
                exit(3);
            }

        else if (getRow()==1)
            return getArray()[0][0];

        else if (getRow()==2)
            return (getArray()[0][0]*getArray()[1][1]) - (getArray()[0][1]*getArray()[1][0]);

        else
            {
                float det=0;
                Matrix m2(getRow()-1,getCol()-1);
                for(int x=0;x<getRow();x++)
                    {
                        int subi=0;
                        for(int i=1;i<getCol();i++)
                        {
                            int subj=0;
                            for(int j=0;j<getCol();j++)
                                {
                                    if(j==x)
                                        continue;
                                    m2.getArray()[subi][subj]=getArray()[i][j];
                                    subj++;
                                }
                            subi++;
                        }
                        det=det+(pow(-1,x)*getArray()[0][x]*m2.Determinant());
                    }
                return det;
            }
    return 1;           // any value could be used here as function will never reach here.
    }

    bool isOrthagonal()                              // return true if matrix is orthagonal.
    {return TransposeMult()==Identity(getRow());}

    bool isInvertible()                             // return true if matrix is invertible.
    {return Determinant()!=0;}

    bool isSymmeteric()                            // check if the matrix is symmeteric or not.
    {return (*this) == Transpose();}

    bool isSkewSymmeteric()
    {return (*this) == (Transpose()/-1);}

    void RandomFill(bool include_neg=true,int maxlimit=10)
    {
        srand(time(0));
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                {
                    if(include_neg)
                        getArray()[i][j]= ((rand()-rand())%(maxlimit+1));
                    else
                        getArray()[i][j]= (rand())%(maxlimit+1);
                }
        }
    }

    void Sort()    // sorts the current matrix.
    {
        int r=getRow();
        int c=getCol();
        Matrix rmat=RowMatrix();
        for(int i=0;i<getRow()*getCol();i++)  //Bubble Sort.
        {
            for(int j=i+1;j<getRow()*getCol();j++)
            {
                if(rmat.getArray()[0][i]>rmat.getArray()[0][j])
                    swap(rmat.getArray()[0][i],rmat.getArray()[0][j]);

            }

        }
        rmat.Reshape(r,c);
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
            {
                getArray()[i][j]=rmat.getArray()[i][j];
            }
        }
    }

    void Reshape(int p,int q)   // matrix with same enteries but different shape.
    {
        if((getRow()*getCol()) !=(p*q))
        {
            cout<<"Matrix cannot be reshaped from "<<getRow()<<"x"<<getCol()<<" to "<<p<<"x"<<q;
            exit(4);
        }

        //could have used realloc,but other approach was also good!
        Matrix temp=RowMatrix();
        set(p,q);  //the trick was to call set from here
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<q;j++)
                getArray()[i][j]=temp.getArray()[0][i*q+j];

        }
    }

    Matrix Shape()                                // return the shape of the matrix as a matrix
    {
        Matrix temp(2,1);
        temp.getArray()[0][0]=getRow();
        temp.getArray()[0][1]=getCol();
        return temp;
    }

    Matrix Sin()                                  // calculates the Sin of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=sin(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Cos()                                  // calculates the Cos of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=cos(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Tan()                                  // calculates the Tan of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=tan(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Sinh()                                  // calculates the Sinh of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=sinh(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Cosh()                                  // calculates the Cosh of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=cosh(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Tanh()                                  // calculates the Tanh of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=tanh(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Asin()                                  // calculates the inverse sin of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=asin(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Acos()                                  // calculates the inverse cos of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=acos(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Atan()                                  // calculates the inverse tan of matrix, element wise.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                temp.getArray()[i][j]=atan(getArray()[i][j]);
        }
        return temp;
    }

    Matrix Transpose()  //returns the transpose of the matrix
    {
        Matrix temp(getCol(),getRow());
        for(int i=0;i<temp.getRow();i++)
            {
                for(int j=0;j<temp.getCol();j++)
                    {
                        temp.getArray()[i][j]=getArray()[j][i];
                    }

            }
        return temp;
    }

    Matrix Power(int n)   // returns the matrix to the power of n.
    {
        Matrix temp2=(*this).Identity(getRow());
        for(int i=0;i<n;i++)
            {
                temp2=temp2*(*this);
            }

        return temp2;
    }

    Matrix RowMatrix(bool rmajor=true)  // return the row matrix from the given matrix.(by default row major type)
    {
        Matrix temp(1,getRow()*getCol());
        for(int i=0;i<getRow();i++)
            {
                if (rmajor)
                {
                    for(int j=0;j<getCol();j++)
                        temp.getArray()[0][getCol()*i+j]=getArray()[i][j];
                }
                else
                {
                    for(int j=0;j<getCol();j++)
                        temp.getArray()[0][getRow()*j+i]=getArray()[i][j];
                }
            }
        return temp;
    }

    Matrix ColMatrix(bool rmajor=true)  // return the column matrix from the given matrix.(by default row major type)
    {
        Matrix temp(getRow()*getCol(),1);
        for(int i=0;i<getRow();i++)
            {

                if(rmajor)
                {
                    for(int j=0;j<getCol();j++)
                        temp.getArray()[getCol()*i+j][0]=getArray()[i][j];
                }
                else
                {
                    for(int j=0;j<getCol();j++)
                        temp.getArray()[getRow()*j+i][0]=getArray()[i][j];
                }
            }
        return temp;
    }

    Matrix Inverse()                        //returns the inverse of the matrix.
    {
        if(isInvertible()==false)
            {
                cout<<"Determiniant is zero,Inverse doesn't exist(Matrix is singular!)";
                exit(3);
            }

       return AdjointMatrix()/Determinant();
    }

    Matrix AdjointMatrix()                 //returns the adjont of the matrix.
    {return CofactorMatrix().Transpose();}

    Matrix getMinor(int rindex,int cindex)  //returns the minor matrix of a given index (rindex,cindex) [0 indexed]
    {
        //not my way(i could'nt figure it out!)
        if(getRow()!=getCol())
            {
                cout<<"Minor doesn't exist for non sqauare matricies.";
                exit(3);
            }
        int i=0,j=0;
        Matrix temp(getRow()-1,getCol()-1);
            for(int r=0;r<getRow();r++)
                {
                    for(int c=0;c<getCol();c++)
                        {
                            if(r!=rindex && c!=cindex)
                            {
                                temp.getArray()[i][j++]=getArray()[r][c];
                                    if(j==getRow()-1)
                                    {
                                        j=0;
                                        i++;
                                    }
                            }
                        }
                   }

        return temp;
    }

    Matrix CofactorMatrix()         //returns the cofactor matrix of a given matrix.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                {

                    temp.getArray()[i][j]=pow(-1,i+j)*(getMinor(i,j).Determinant());
                }
        }

        return temp;
    }

    Matrix MinorMatrix()       //returns the minor matrix from the given matrix.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
            {
                temp.getArray()[i][j]=pow(-1,i+j)*(CofactorMatrix().getArray()[i][j]);
            }

        }
        return temp;
    }

    Matrix LowerTriangleMatrix()         //return the lower triangular matrix from the given matrix.
    {
        Matrix ltm(getRow(),getCol());

        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                {
                    if(i>=j)
                        ltm.getArray()[i][j]=getArray()[i][j];
                }
        }
        return ltm;
    }

    Matrix UpperTriangleMatrix()       //return the upper triangular matrix from the given matrix
    {
        Matrix utm(getRow(),getCol());

        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                {
                    if(i<=j)
                        utm.getArray()[i][j]=getArray()[i][j];
                }

        }
        return utm;
    }

    Matrix EigenValues()  // returns the Eigenvalues of the matrix (in a matrix form(not how it is supposed to be(Eigen vals and vects are different)))
    {
        Matrix temp(getRow(),getCol());
        if(getRow()!=getCol())
            {
                cout<<"Can't find EigenVals for non-square matricies!";
                exit(3);
            }
        else if (getRow()<2)
            {
                cout<<"Can't find EigenVals for matricies < order 2";

            }
        else if(getRow()==2)  // I know only how to do it for degree 2 polynomial (In order 2,characteristic polynomial is of degree 2->hence quadratic formulae)
        {
            float lambda1,labda2;
            temp.getArray()[0][0]=0.5*((getArray()[0][0]+getArray()[1][1]) + sqrt(4*getArray()[0][1]*getArray()[1][0]+pow((getArray()[0][0]-getArray()[1][1]),2)));
            temp.getArray()[1][1]=0.5*((getArray()[0][0]+getArray()[1][1]) - sqrt(4*getArray()[0][1]*getArray()[1][0]+pow((getArray()[0][0]-getArray()[1][1]),2)));
        }


        return temp;
    }

    Matrix DiagonalMatrix()  // return diagonal matrix from the given matrix.
    {
        if(getRow()!=getCol())
            {
                cout<<"Diagonal Matrix only exists for square matricies"<<endl;
                exit(3);
            }
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
            {
                if(i==j)
                    temp.getArray()[i][j]=getArray()[i][j];
            }
        }
        return temp;
    }

    Matrix Identity(int n)          //returns the Identity matrix of order n.(it should be outside ,but it is needed by other fuctions.)
    {
        Matrix iden(n,n);
        for(int i=0;i<n;i++)
            {
            for(int j=0;j<n;j++)
                {
                    if(i==j)
                        iden.getArray()[i][j]=1;
                    else
                        iden.getArray()[i][j]=0;
                }
            }
        return iden;
    }

    Matrix Ones(int n)          //returns the nxn matrix with all enteries 1.
    {
        Matrix iden(n,n);
        for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                    iden.getArray()[i][j]=1;
            }
        return iden;
    }

    Matrix Zeros(int n)        // returns the nxn matrix with all enteries 0.
    {
        Matrix zero(n,n);     //since we have used calloc,all values by default are zero.
        return zero;
    }

    Matrix TransposeMult()   // returns the multiplication of matrix with its transpose.
    {
        Matrix res=(*this)*(Transpose());
        return res;
    }

    // Operator overloading for matrix class

    Matrix operator+(const Matrix& m2)          //overlodes + operator and returns the sum of the matricies.
    {
         Matrix temp(getRow(),getCol());
        if(getRow()!= m2.getRow() || getCol()!=m2.getCol())
            {
                cout<<"Matrix cannot be added ! Terminating program"<<endl;
                exit(3);
            }
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {temp.getArray()[i][j]=getArray()[i][j]+m2.getArray()[i][j];}
            }
        return temp;
    }
    Matrix operator-(const Matrix& m2)    //overlodes - operator and returns the difference of the matricies.
    {
            Matrix temp(getRow(),getCol());
        if(getRow()!= m2.getRow() || getCol()!=m2.getCol())
            {
                cout<<"Matrix cannot be subtracted ! Terminating program"<<endl;
                exit(3);
            }
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {temp.getArray()[i][j]=getArray()[i][j]-m2.getArray()[i][j];}
            }
        return temp;
    }

    Matrix operator*(const Matrix& m2)    //overlodes * operator and returns the product of the matricies.
    {
        Matrix temp(getRow(),m2.getCol());
        if(getCol()!= m2.getRow())
            {
                cout<<"Matrix cannot be multiplied! Terminating program"<<endl;
                exit(3);
            }
        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<m2.getCol();j++)

                    for(int k=0;k<getCol();k++)
                    {temp.getArray()[i][j]+=(getArray()[i][k]*m2.getArray()[k][j]);}
            }
        return temp;
    }


    Matrix operator/(const int factor)   //overload / operator to return matrix in which each element is divided by factor.
    {
        Matrix temp(getRow(),getCol());
        for(int i=0;i<getRow();i++)
        {
            for(int j=0;j<getCol();j++)
                {
                    temp.getArray()[i][j]=getArray()[i][j]/factor;
                }
        }
      return temp;
    }

    bool operator==(const Matrix& m2)  //overlodes == operator to check wheather two matricies are equal or not.
    {
        if(getRow()!=m2.getRow() || getCol()!=m2.getCol())
                return false;

        for(int i=0;i<getRow();i++)
            {
                for(int j=0;j<getCol();j++)
                    {
                        if(getArray()[i][j]!=m2.getArray()[i][j])
                            return false;
                    }
            }
        return true;
    }
};

int main()
{
    //Test

    Matrix m1(3,3);
    m1.RandomFill();
    m1.showMatrix();
    cout<<endl<<endl;
    Matrix m3=m1.Inverse();
    m3.showMatrix();
    return 0;
}
