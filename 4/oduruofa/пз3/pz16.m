alpha=0.5;
ro=0.5;
eps=10^-3;
N_apr = ceil(log((eps * (1 - alpha)) / ro) / log(alpha)) + 1;
fprintf("Число априорных итераций: %d\n", N_apr);

syms t s


t_old = 1;

for n = 1:N_apr
    integrand = (1 - t*s) * subs(t_old, t, s);
    integral_val = int(integrand, s, 0, 1);
    t_new = 0.5 * integral_val + t;
    t_new = simplify(t_new);
    t_old = t_new;
end
fprintf("11 приближение: x_%d(t)=",N_apr);
disp(t_new);

x_t = (24/31)*t+(12/31);
t_values = linspace(0, 1, 2);
x_t_f = matlabFunction(x_t);
x11_f = matlabFunction(t_new);
x_t_val = x_t_f(t_values);
x11_val = x11_f(t_values);


diff = abs(x_t_val - x11_val);
max_diff = max(diff);
fprintf('Метрика ro_{C[0,1]}(x_t, x11) = %f\n', max_diff);