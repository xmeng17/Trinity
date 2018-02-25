trinity: main.c particle.c ukf.c linear.c geo.c measure.c motion.c stats.c
	gcc -o trinity main.c particle.c ukf.c linear.c geo.c measure.c motion.c stats.c -lm
