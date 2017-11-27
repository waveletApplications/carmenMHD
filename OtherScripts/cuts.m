clear all;
close all;
clc;


f1 = load('OT_2D_L9_eps001J_id_Y.dat'); #001J
f2 = load('OT_2D_L9_eps003J_id_Y.dat'); #003J
f3 = load('OT_2D_L9_eps02_id_Y.dat'); #02
f5 = load('OT_2D_L9_id_y.dat'); #flash

figure(1)


plot(f1(:,1),f5(:,1),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,4),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,4),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,4),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("RHO", "fontsize", 15) 
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("RHO", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_rho_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,2),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,5),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,5),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,5),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("PRE", "fontsize", 15) 
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("PRE", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_pre_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,3),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,6),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,6),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,6),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("VX", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vx_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,4),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,7),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,7),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,7),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("RHO", "fontsize", 15) 
axis([0 2*pi])
#axis([0 1 -4.5 4.5])

xlabel ("x", "fontsize", 18);
ylabel ("VY", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vy_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,5),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,8),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,8),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,8),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)

#axis([0 1 -4.5 4.5])
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("VZ", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vz_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,6),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,9),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,9),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,9),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("RHO", "fontsize", 15) 
#axis([0 1 -1. 3.1])
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("BX", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_bx_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,7),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,10),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,10),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,10),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("RHO", "fontsize", 15) 
#axis([0 1 -1. 3.1])
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("BY", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_by_cutypi.eps','-deps');

close all

plot(f1(:,1),f5(:,8),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,1),f1(1:15:512,11),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,1),f2(1:15:512,11),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,1),f3(1:15:512,11),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#title ("RHO", "fontsize", 15) 
#axis([0 1 -1. 3.1])
axis([0 2*pi])
xlabel ("x", "fontsize", 18);
ylabel ("BZ", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_bz_cutypi.eps','-deps');

close all

clear all

f1 = load('OT_2D_L9_eps001J_id_X.dat'); #001J
f2 = load('OT_2D_L9_eps003J_id_X.dat'); #003J
f3 = load('OT_2D_L9_eps02_id_X.dat'); #02
f5 = load('OT_2D_L9_id_x.dat'); #flash


figure(1)


plot(f1(:,2),f5(:,1),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,4),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,4),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,4),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 0.6 1.1])
axis([0 2*pi])
xlabel ("y", "fontsize", 18);
ylabel ("RHO", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_rho_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,2),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,5),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,5),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,5),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 0.6 1.1])
axis([0 2*pi])
xlabel ("y", "fontsize", 18);
ylabel ("PRE", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_pre_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,3),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,6),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,6),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,6),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -0.7 0.5])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("VX", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vx_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,4),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,7),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,7),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,7),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -0.7 0.5])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("VY", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vy_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,5),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,8),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,8),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,8),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -0.7 0.5])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("VZ", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')
print('OT_2D_L9_vz_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,6),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,9),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,9),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,9),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -1 3.1])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("BX", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_bx_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,7),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,10),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,10),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,10),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -1 3.1])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("BY", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_by_cutxpi.eps','-deps');

close all

plot(f1(:,2),f5(:,8),'-k;Reference;','linewidth',2,'Color',[0 0 0]+0.6)
hold on
plot(f1(1:15:512,2),f1(1:15:512,11),'xk;EPS001;','markersize',10,'linewidth',1);
hold on
plot(f1(1:15:512,2),f2(1:15:512,11),'ok;EPS003;','linewidth',1)
hold on
plot(f1(1:15:512,2),f3(1:15:512,11),'*;EPS-02;','linewidth',3,'Color',[0 0 0]+0.4)
#axis([-1 1 -1 3.1])
axis([0 2*pi])

xlabel ("y", "fontsize", 18);
ylabel ("BZ", "fontsize", 18);
set(gca,'fontsize',18);
#h=legend ("location", 'northoutside',"orientation", "horizontal")
#set (h, "fontsize", 15);
b=gca;
legend(b,'off')

print('OT_2D_L9_bz_cutxpi.eps','-deps');

close all

