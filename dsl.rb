class Definition

  def self.build
    gemfile = Bundler::SharedHelpers.default_gemfile
    gemfile = Pathname.new(gemfile).expand_path
    if not gemfile.file?
      raise GemfileNotFound, "#{gemfile} not found"
    end

    lockfile = Bundler::SharedHelpers.default_lockfile
    unlock = {}

    Dsl.evaluate gemfile, lockfile, unlock
  end
end
class Dsl < Bundler::Dsl

  def gem(name, *args)
    options = args.last.is_a?(Hash) ? args.pop : {}
    if options[:type] == :development
      options[:type] = :runtime
      super name, *args, options
    end
  end
end
Bundler::Installer.install Bundler.root, Definition.build
puts 'Your bundle is complete!'
puts 'Use `bundle show [gemname]` to see where a bundled gem is installed.'
