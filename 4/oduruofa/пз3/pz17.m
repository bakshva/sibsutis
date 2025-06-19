t = linspace(0, 16, 1000);
max_iter = 6;  

x_exact = -2*exp(sin(t)) + sin(t) + 1;


x_iter = zeros(max_iter, 1000);
x_iter(1,:) = t; 


for n = 2:max_iter
    for i = 1:1000
        ti = t(1:i);
        integrand = cos(ti) .* x_iter(n-1,1:i);
        if length(ti) > 1
            x_iter(n,i) = trapz(ti, integrand) - 0.25*(3 + cos(2*t(i))); 
        else
            x_iter(n,i) = -0.25*(3 + cos(2*t(i))); 
        end
    end
end

figure('Name', '4-я итерация', 'Position', [100 400 600 400]);
plot(t, x_iter(4,:), 'r', 'LineWidth', 2);
hold on;
plot(t, x_exact, 'k--', 'LineWidth', 2);
hold off;
ylim([-6 4]); 
xlim([0 16]);
legend('x₄(t)', 'Точное решение', 'Location', 'best');
grid on;


figure('Name', '5-я итерация', 'Position', [750 400 600 400]);
plot(t, x_iter(5,:), 'g', 'LineWidth', 2);
hold on;
plot(t, x_exact, 'k--', 'LineWidth', 2);
hold off;
ylim([-3.5 3]);
xlim([0 16]);
legend('x₅(t)', 'Точное решение', 'Location', 'best');
grid on;


figure('Name', '6-я итерация', 'Position', [1400 400 600 400]);
plot(t, x_iter(6,:), 'b', 'LineWidth', 2);
hold on;
plot(t, x_exact, 'k--', 'LineWidth', 2);
hold off;
ylim([-3.5 0.5]);
xlim([0 16]);
legend('x₆(t)', 'Точное решение', 'Location', 'best');
grid on;

