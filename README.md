# ipfilter

Сортировка ip адресов в обратном лексикографическом порядке.

Для установки добавить к списку репозиториев:    
`echo "deb http://dl.bintray.com/ivanleb/otus-cpp trusty main" | sudo tee -a /etc/apt/sources.list`

установить приложение:    
`sudo apt-get update && sudo apt install -y ip_filter`

запустить:     
`cat ip_filter.tsv | ip_filter > out.tsv`

