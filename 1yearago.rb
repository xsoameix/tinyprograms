
  # Use format to parse string & substitude the part of it.
  def sub_with(str, format, &substitute_func)
    regexs = select_regexs format[:format]
    regexs.each do |regex|
      if str =~ regex
        date = [$1, $2, $3].map(&:to_i) # Eg: [102, 5, 1]
        date = substitute_func.call LocaleDate.new(date)
        return date.map { |x| '%02d' % x }.join('/') # Eg: '2013/05/01'
      end
    end

    str
  end

  # Use format to select corresponding regex.
  # fomat examples: [:digits, :split] and {inverted: [:digits, :split]}
  def select_regexs(format)
    options = {digits: /(\d{2,4})(\d{2})(\d{2})/,
               split: /(\d{2,4})[^\d]+(\d{1,2})[^\d]+(\d{1,2})/,
               inverted: {digits: /(\d{2})(\d{2})(\d{2,4})/,
                          split: /(\d{1,2})[^\d]+?(\d{1,2})[^\d]+?(\d{2,4})/}}
    fletten = proc do |format, options|
      regexs = []
      case format
      when Array then
        format.map { |format| regexs += fletten.call(format, options) }
      when Hash
        format.map { |key, format| regexs += fletten.call(format, options[key]) }
      when Symbol
        regexs << options[format]
      end
      regexs
    end
    fletten.call format, options
  end

  class LocaleDate

    def initialize date
      @date = date
      @year, @i = @date.each_with_index.max # 民國31年前不適用XD
    end

    # 避免取得四碼西元年
    def in_ad_years
      @date[@i] = (@year.to_s.length <= 3) ? (@year + 1911) : @year
      @date
    end

    # 避免取得二到三碼民國年
    def in_tw_years
      @date[@i] = (@year.to_s.length >= 4) ? (@year - 1911) : @year
      @date
    end
  end
