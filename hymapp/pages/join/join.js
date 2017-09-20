Page({
  data: {
    appid: 'wx22b3f0e602de02aa',//appid需自己提供，此处的appid我随机编写  
    secret: '44839a2db254c9080d93d64804941890'//secret需自己提供，此处的secret我随机编写  
  },
  onLoad: function (options) {

  },
  onReady: function () {

  },
  onShow: function () {

  },
  onHide: function () {

  },
  onUnload: function () {

  },
  onPullDownRefresh: function () {

  },
  onReachBottom: function () {

  },
  showTopTips2:function(){
    var that = this.data;
    console.log(that.appid);
    wx.login({
      success: function (res){
      console.log(res.code);

      var l = 'https://api.weixin.qq.com/sns/jscode2session?appid=' + that.appid + '&secret=' + that.secret + '&js_code=' + res.code + '&grant_type=authorization_code'; 
      console.log(l);
      wx.request({
        url: l,
        data: {},
        method: 'GET', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT    
        // header: {}, // 设置请求的 header    
        success: function (res) {
          var obj = {};
          obj.openid = res.openid;
          obj.expires_in = Date.now() + res.data.expires_in;
          console.log(res);  
          wx.setStorageSync('user', obj);//存储openid    
        }
      });   
      }
    })
  },
  showTopTips: function () {

      var that = this
      wx.login({
        success: function (res) {
          console.log("res.code=====" + res.code);
          if (res.code) {
            //发起网络请求
            wx.request({
              url: 'https://api.weixin.qq.com/sns/jscode2session?appid=wx22b3f0e602de02aa&secret=44839a2db254c9080d93d64804941890&js_code=' + res.code + '&grant_type=authorization_code',
              method: "POST",
              success: function (res) {

                that.setData({
                  openid: res.data.openid
                })
              }
            })
          } else {
            console.log('获取用户登录态失败！' + res.errMsg)
          }
        }
      });
    
  }
})        