alpha = 1-((sqrt(3)-1)/(sqrt(3)+4));
eps = 10^-5;
ro=0.19315;
N_apr = ceil(log((eps * (1 - alpha))/ro) / log(alpha)) + 1;
x_old = 0;


phi = @(x) (x-(x*sqrt(3)+atan(3*x-2)-(sin(x))^2)/(sqrt(3)+4));

for i = 1:N_apr
    x_new = phi(x_old);
    if abs(x_new - x_old) <= eps
        break;
    end
    x_old = x_new;
end


fprintf('Приближенное решение: x = %.5f\n', x_new);
fprintf('Число итераций: %d\n', i);
fprintf('Число априорных итераций: %d\n', N_apr);
