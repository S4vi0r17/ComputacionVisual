void circunferencia_punto_medio(int R)
{
    // discretizacion valida en el II octante
    int x = 0;
    int y = R, d = 1 - R;
    pintar(x, y);
    pintar(y, x);
    pintar(y, -x);
    pintar(x, -y);
    pintar(-x, -y);
    pintar(-y, -x);
    pintar(-y, x);
    pintar(-x, y);
    while (x < y)
    {
        if (d < 0)
            d += 2 * x + 3;
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        pintar(x, y);
        pintar(y, x);
        pintar(y, -x);
        pintar(x, -y);
        pintar(-x, -y);
        pintar(-y, -x);
        pintar(-y, x);
        pintar(-x, y);
    }
}