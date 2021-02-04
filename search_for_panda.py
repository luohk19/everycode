from selenium import webdriver
# from selenium.webdriver.common.keys import Keys
import time
path = 'C:\\Users\\Administrator\\Desktop\\python\\chromedriver'
browser = webdriver.Chrome(executable_path=path)
browser.get('http://baidu.com')
time.sleep(3)
browser.save_screenshot('firstpage.png')
baidu_input = browser.find_element_by_id('kw')
baidu_input.send_keys('大熊猫')
browser.find_element_by_id('su').click()
