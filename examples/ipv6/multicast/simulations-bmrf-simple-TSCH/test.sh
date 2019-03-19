IDs=( $(echo "1 2 3 4 5 6" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )

for id in "${!IDs[@]}"
do
	sed -i s/\#ID"$id"\#/${IDs[id]}/ "test.txt"
	echo ${IDs[id]}
done
