import requests
from requests.models import cookiejar_from_dict


class Request_Spider(object):
    def __init__(self):
        url = 'http://www.baidu.com'
        header = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1'
        }
        self.response = requests.get(url, headers=header)

    def run(self):
        data = self.response.content.decode("utf-8")
        # 1 获取请求头
        request_headers = self.response.request.headers

        # 2 获取响应头
        response_headers = self.response.headers
        
        # 3 获取响应状态码
        code = self.response.status_code
        
        # 4 请求的cookie
        request_cookie = self.response.request._cookies

        # 5 相应的cookie
        response_cookie = self.response.cookies


Request_Spider().run()
