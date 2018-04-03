class matrix
{
  private:
    int tab[102][102];
    int columns;
    int rows;
    bool error; 

  public:
    matrix(const int rows = 0, const int columns = 0, bool error = 0)
    {
        this->rows = rows;
        this->columns = columns;
        this->error = error;
    }

    friend matrix operator+(const matrix &a, const matrix &b);
    friend matrix operator*(const matrix &a, const matrix &b);
    friend matrix operator^(const matrix &a, int p);
    friend ostream &operator<<(ostream &stream, const matrix &a);
    friend istream &operator>>(istream &stream, matrix &a);
};

matrix operator+(const matrix &a, const matrix &b)
{
    if (a.columns != b.columns || a.rows != b.rows)
    {
        matrix result(0, 0, true);
        return result;
    }

    matrix result(a.rows, a.columns, false);
    for (int y = 0; y < a.rows; y++)
    {
        for (int x = 0; x < a.columns; x++)
        {
            int sum = a.tab[y][x] + b.tab[y][x];
            sum %= 1000;
            result.tab[y][x] = sum;
        }
    }
    return result;
}

matrix operator*(const matrix &a, const matrix &b)
{
    if (a.columns != b.rows)
    {
        matrix result(0, 0, true);
        return result;
    }

    matrix result(a.rows, b.columns, false); // = new matrix(a.rows, b.columns, false);

    for (int y = 0; y < result.rows; y++)
    {
        for (int x = 0; x < result.columns; x++)
        {
            int sum = 0;
            for (int z = 0; z < a.columns; z++)
            {
                sum += a.tab[y][z] * b.tab[z][x];
                sum %= 1000;
            }
            result.tab[y][x] = sum;
        }
    }
    return result;
}

matrix operator^(const matrix &a, int p)
{
    if (a.columns != a.rows)
    {
        matrix result(0, 0, true);
        return result;
    }
    int size = a.columns;
    matrix result(size, size, false);

    if (p == 0)
    {
        for (int x=0; x<size; x++)
        {
            for (int y=0; y<size; y++)
            {
                result.tab[y][x] = 0;
            }
        }
        for (int i = 0; i < size; i++)
        {
            result.tab[i][i] = 1;
        }
        return result;
    }

    if (p % 2 == 1)
    {
        matrix temp = a ^ ((p - 1) / 2);
        temp = temp * temp;
        return a * temp;
    }
    else
    {
        matrix temp = a ^ (p / 2);
        return temp * temp;
    }
}

istream &operator>>(istream &stream, matrix &a)
{
    for (int y = 0; y < a.rows; y++)
    {
        for (int x = 0; x < a.columns; x++)
        {
            int value;
            stream >> value;
            a.tab[y][x] = value;
        }
    }
    return stream;
}

ostream &operator<<(ostream &stream, const matrix &a)
{
    if (a.error)
    {
        stream << "ERROR" << endl;
    }
    else
    {
        for (int y = 0; y < a.rows; y++)
        {
            for (int x = 0; x < a.columns; x++)
            {
                stream << (a.tab[y][x] % 1000) << " ";
            }
            stream << endl;
        }
    }
    return stream;
}