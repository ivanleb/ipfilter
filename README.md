# ipfilter

Сортировка ip адресов в обратном лексикографическом порядке.

Добавить к списку репозиториев:    
`echo "deb http://dl.bintray.com/ivanleb/otus-cpp trusty main" | sudo tee -a /etc/apt/sources.list`

Установить приложение:    
`sudo apt-get update && sudo apt install -y ip_filter`

Запустить:     
`cat ip_filter.tsv | ip_filter > out.tsv`

