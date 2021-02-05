import requests


url = "https://www.yaozh.com/login"

login_form_data = {
    "type": "0",
    "username": "luohk19",
    "pwd": "2396094263a",
    "country": "86_zh-CN",
    "formhash": "B2B384F65D",
    "backurl": "https%3A%2F%2Fwww.yaozh.com%2F"
}

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.66 Safari/537.36"
}

session = requests.session()

cookies = "acw_tc=2f624a4616124919858278489e4e3a6c4cd75d79b43c5964cd903d39d14c5d; PHPSESSID=3cr76h79akposkae6tav20cke2; _ga=GA1.2.101716400.1612491986; _gid=GA1.2.289767148.1612491986; Hm_lvt_65968db3ac154c3089d7f9a4cbb98c94=1612491986; yaozh_userId=1041013; _gat=1; Hm_lpvt_65968db3ac154c3089d7f9a4cbb98c94=1612492060; yaozh_uidhas=1; yaozh_mylogin=1612492064; acw_tc=2f624a4616124919858278489e4e3a6c4cd75d79b43c5964cd903d39d14c5d; UtzD_f52b_saltkey=qbpi9z59; UtzD_f52b_lastvisit=1612488468; UtzD_f52b_lastact=1612492068%09uc.php%09; _ga=GA1.1.1881538956.1612492071; _gid=GA1.1.1721171735.1612492071; _gat=1"

cookie_list = cookies.split('; ')

cookie_dict = {cookie.split('=')[0]: cookie.split('=')[1] for cookie in cookie_list}

response = session.post(url, data=login_form_data, headers=headers)

data = session.get(url, headers=headers).content.decode()

with open("1.html", "w", encoding="utf-8") as f:
    f.write(data)
