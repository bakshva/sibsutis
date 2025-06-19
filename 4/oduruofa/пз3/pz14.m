eps1=10^-2;
eps2=10^-4;


A = [4, 7, 2, 8;
     5, 1, 1, 9;
     3, 3, 6, 4;
     1, 5, 8, 7];
b = [77; 62; 59; 84];
%det=det(A);

%fprintf("Определитель: %.1f\n",det);

At=transpose(A);
la=(max(eig(At*A),[],'all'));
fprintf("Максимальное собственное число матрицы А: %.5f\n",la);

I=eye(4);
C=I-(At*A)/la;
fprintf('Матрица C:\n'); 
disp(C);
d=(At*b)/la;
fprintf('Вектор d:\n'); 
disp(d);
lc=sym(max(eig(C),[],'all'));
fprintf("Максимальное собственное число матрицы С: %.5f\n",lc);

alpha=0.98965;
x0=[1;2;3;4];
xn = @(x) (C*x+d);
x1=xn(x0);
fprintf('Вектор первой итерации:\n'); 
disp(x1);

ro=norm(x0-x1,2);
chis1=sym(eps1*(1-alpha));
v1=chis1/ro;
chis2=sym(eps2*(1-alpha));
v2=chis2/ro;
N_apr1=ceil(log(v1)/log(alpha))+1;
fprintf('Число априорных итераций для точности 10^-2: %d\n', N_apr1);
N_apr2=ceil(log(v2)/log(alpha))+1;
fprintf('Число априорных итераций для точности 10^-4: %d\n', N_apr2);

x_toch=[2;3;4;5];

x_old=[1;2;3;4];
for i = 1:N_apr1
    x_new = xn(x_old);
    if (alpha/(1-alpha))*norm(x_new-x_old,2) <= eps1
        break;
    end
    x_old = x_new;
end

fprintf('Решение с точность 10^-2:\n'); 
disp(x_new);
fprintf('Количество итераций: %d\n', i);
fprintf('Сравнение точного решения с приближенным: %.6f\n',norm(x_new - x_toch, 2));

for i = 1:N_apr2
    x_new = xn(x_old);
    if (alpha/(1-alpha))*norm(x_new-x_old,2) <= eps2
        break;
    end
    x_old = x_new;
end
fprintf('Решение с точность 10^-4:\n'); 
disp(x_new);
fprintf('Количество итераций: %d\n', i);
fprintf('Сравнение точного решения с приближенным: %.6f\n',norm(x_new - x_toch, 2));