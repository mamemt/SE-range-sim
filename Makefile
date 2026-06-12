range-sim: main.o battery.o menu.o route.o vehicle.o weather.o json_importer.o calculation.o
	gcc -o range-sim main.o battery.o menu.o route.o vehicle.o weather.o json_importer.o calculation.o

main.o: src/main.c
	gcc -Iinclude -c src/main.c

battery.o: src/battery.c
	gcc -Iinclude -c src/battery.c

menu.o: src/menu.c
	gcc -Iinclude -c src/menu.c

route.o: src/route.c
	gcc -Iinclude -c src/route.c

vehicle.o: src/vehicle.c
	gcc -Iinclude -c src/vehicle.c

weather.o: src/weather.c
	gcc -Iinclude -c src/weather.c

json_importer.o: src/json_importer.c
	gcc -Iinclude -c src/json_importer.c

calculation.o: src/calculation.c
	gcc -Iinclude -c src/calculation.c

test: test_json_importer
	./test_json_importer

test_json_importer: tests/test_json_importer.c src/json_importer.c tests/unity/unity.c
	gcc -Iinclude -Itests/unity -DUNITY_INCLUDE_DOUBLE -o test_json_importer tests/test_json_importer.c src/json_importer.c tests/unity/unity.c