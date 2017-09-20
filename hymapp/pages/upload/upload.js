Page({
  data: {
    files: []
  },

  chooseImage1: function (e) {
    var that = this;
    wx.chooseImage({
      sizeType: ['original', 'compressed'], // 可以指定是原图还是压缩图，默认二者都有
      sourceType: ['album', 'camera'], // 可以指定来源是相册还是相机，默认二者都有
      success: function (res) {
        console.log(that.data.files.concat(res.tempFilePaths));
        // 返回选定照片的本地文件路径列表，tempFilePath可以作为img标签的src属性显示图片
        that.setData({
          files: that.data.files.concat(res.tempFilePaths)
        });
      }
    })
  },

  chooseImage: function (e) {
    var that = this;
    wx.chooseImage({
      success: function (res) {
        var tempFilePaths = res.tempFilePaths
        console.log(res.tempFilePaths);
        wx.uploadFile({
          url: 'http://aa.cc/', //仅为示例，非真实的接口地址
          filePath: tempFilePaths[0],
          name: 'file',
          formData: {
            'user': 'test'
          },
          success: function (res) {
            var data = res.data;
            console.log(res);
            //do something
          },
          fail:function(res){
            console.log(res);
          }
        })
      }
    })
  },
  previewImage: function (e) {
    wx.previewImage({
      current: e.currentTarget.id, // 当前显示图片的http链接
      urls: this.data.files // 需要预览的图片http链接列表
    })
  }
});