alpha=2/exp(1);
eps=10^-2;
ro=2/exp(1);

N_apr = ceil(log((eps * (1 - alpha))/ro) / log(alpha)) + 1;
fprintf("Число априорных итераций: %d\n",N_apr);

t_min = -5;
t_max = 5;
t_step = 0.1;
t = t_min:t_step:t_max;

x_old=cos(2*t);
phi=@(x,t) ((2./exp(1+abs(x))+cos(2*t)));

for i = 1:N_apr
    x_new = phi(x_old, t);
    x_old = x_new; 
end

x_s = @(t_v) interp1(t, x_new, t_v);

figure;
fplot(x_s, [t_min, t_max], 'LineWidth', 2);
xlabel('t');
ylabel('x(t)');
grid on;