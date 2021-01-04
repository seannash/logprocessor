all:
	make -C src all
	src/monitor_unit_tests

clean:
	make -C src clean

sample: all
	src/monitor data/sample_csv.txt

docker:
	sudo docker run -v `pwd`:/work --workdir=/work -it gcc:10
