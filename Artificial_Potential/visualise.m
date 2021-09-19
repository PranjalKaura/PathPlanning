Q = out.Q.Data;
start = [1;1];
goal = [20;20];
x = Q(:, 1);
y = Q(:, 2);
obstacles = out.obs.Data;%r, x, y
centers = obstacles(:, 2:3);
radi = obstacles(:, 1);
hold on;
plot(x, y);
text(start(1),start(2),'START', 'Color','Green','FontSize',10, 'FontWeight', 'bold');
text(goal(1),goal(2),'GOAL' ,'Color','Green','FontSize',10, 'FontWeight', 'bold');

for i  = 1:size(centers, 1)
    th = 0:pi/100:2*pi;
    xunit = radi(i) * cos(th) + centers(i, 1);
    yunit = radi(i) * sin(th) + centers(i, 2);
    plot(xunit, yunit, 'red--', 'LineWidth', 2);
end
