#include<math.h>
void interest(char **params1)
{ 
    char action[10];
    double principle, rate, time,n;
    strcpy(action,params1[1]);
    if(strstr(action,"-s"))
    {
        printf("Enter principle amount");
			scanf("%lf", &principle);

			printf("Enter time in years");
			scanf("%lf", &time);

			printf("Enter rate annually");
			scanf("%lf", &rate);
            rate=rate/100;

            double si=principle*rate*time;
            printf("%.2lf", si);

    }
    else if(strstr(action, "-c"))
    {
        
			printf("Enter principle amount");
			scanf("%lf", &principle);

			printf("Enter time in years");
			scanf("%lf", &time);

			printf("Enter rate annually");
			scanf("%lf", &rate);

			printf("Enter number of times applied per year");
			scanf("%lf", &n);

			rate=rate/100;
			double power= time*n;
			double ci=principle*(pow((1+rate/n),power));
            printf("%.2lf", ci);

    
}
}